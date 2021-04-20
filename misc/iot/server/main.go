package main

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"io/ioutil"
	"log"
	"math/rand"
	"time"

	coap "github.com/plgd-dev/go-coap/v2"
	"github.com/plgd-dev/go-coap/v2/message"
	"github.com/plgd-dev/go-coap/v2/message/codes"
	"github.com/plgd-dev/go-coap/v2/mux"
)

type ChallengeResponse struct {
	Value      uint32
	Expiration time.Time
}

var challenges map[string]*ChallengeResponse = make(map[string]*ChallengeResponse)

func handle(w mux.ResponseWriter, r *mux.Message) {
	msg := []byte("Flag is located under /flag")
	err := w.SetResponse(codes.Content, message.TextPlain, bytes.NewReader(msg))
	if err != nil {
		log.Printf("cannot set response: %v", err)
	}
}

func flag(w mux.ResponseWriter, r *mux.Message) {
	var msg string
	var code codes.Code

	switch r.Code {
	case codes.GET:
		n1 := rand.Uint32()
		n2 := rand.Uint32()
		x := n1 + n2
		token, err := message.GetToken()
		if err != nil {
			msg = "Error generating token"
			code = codes.InternalServerError
			break
		}

		msg = "! VERIFICATION REQUIRED BEFORE PROCEEDING !\n\n"
		msg += "Please note that the challenge is linked to your token.\n"
		msg += "Challenge is revoked in 5 seconds.\n\n"
		msg += fmt.Sprintf("What is %d + %d?\n", n1, n2)
		msg += fmt.Sprintf("Your token is: %s\n", token)
		msg += "Send your answer as PUT message with 32 bit big endian unsigned integer in payload"
		code = codes.Content

		cr := &ChallengeResponse{
			Value:      x,
			Expiration: time.Now().Local().Add(time.Second * 5),
		}
		challenges[token.String()] = cr

	case codes.PUT:
		expectedResp, ok := challenges[r.Token.String()]
		if !ok {
			msg = "No challenge present for token provided"
			code = codes.BadRequest
			break
		}

		if r.Body == nil {
			msg = "No response present"
			code = codes.BadRequest
			break
		}

		body, err := ioutil.ReadAll(r.Body)
		if err != nil {
			msg = "Error reading body"
			code = codes.InternalServerError
			break
		}

		clientResp := binary.BigEndian.Uint32(body)
		if clientResp != expectedResp.Value {
			msg = "Challenge failed"
			code = codes.Unauthorized
			break
		}

		msg = "Verified. Here you go: ibctf{i0t-sh0ws-u-the_M0N3YY}"
		code = codes.Content
	}

	err := w.SetResponse(code, message.TextPlain, bytes.NewReader([]byte(msg)))
	if err != nil {
		log.Printf("cannot set response: %v", err)
	}
}

func main() {
	ticker := time.NewTicker(time.Second)
	done := make(chan bool)
	go func() {
		for {
			select {
			case <-done:
				return
			case <-ticker.C:
				for k, v := range challenges {
					if v.Expiration.After(time.Now()) {
						delete(challenges, k)
					}
				}
			}
		}
	}()

	r := mux.NewRouter()
	r.Handle("/", mux.HandlerFunc(handle))
	r.Handle("/flag", mux.HandlerFunc(flag))
	if err := coap.ListenAndServe("tcp", ":8443", r); err != nil {
		log.Printf("%v", err)
	}
	ticker.Stop()
	done <- true
}
