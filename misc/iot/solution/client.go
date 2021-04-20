package main

import (
	"bytes"
	"context"
	"io/ioutil"
	"log"
	"regexp"
	"strconv"
	"time"
	"encoding/binary"
	"encoding/hex"
	
	"github.com/plgd-dev/go-coap/v2/tcp"
	"github.com/plgd-dev/go-coap/v2/message"
)

func main() {
	co, _ := tcp.Dial("localhost:8443")
	ctx, cancel := context.WithTimeout(context.Background(), time.Second)
	defer cancel()

	resp, _ := co.Get(ctx, "/flag")
	body, _ := ioutil.ReadAll(resp.Body())
	bodyStr := string(body)
	log.Printf("%v", bodyStr)
	
	re := regexp.MustCompile("What is ([0-9]+) \\+ ([0-9]+)\\?")
	n1, _ := strconv.Atoi(re.FindStringSubmatch(bodyStr)[1])
	n2, _ := strconv.Atoi(re.FindStringSubmatch(bodyStr)[2])
	re = regexp.MustCompile("Your token is: ([a-f0-9]{16})")
	token := re.FindStringSubmatch(bodyStr)[1]
	tokenHex, _ := hex.DecodeString(token)
	
	answer := make([]byte, 4)
	binary.BigEndian.PutUint32(answer, uint32(n1+n2))
	p, _ := tcp.NewPutRequest(context.Background(), "/flag", message.TextPlain, bytes.NewReader(answer))
	p.SetToken(tokenHex)
	
	resp, _ = co.Do(p)
	body, _ = ioutil.ReadAll(resp.Body())
	log.Printf("%v", string(body))
}
