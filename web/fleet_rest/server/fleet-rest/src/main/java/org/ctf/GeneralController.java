package org.ctf;

import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class GeneralController {

    @RequestMapping(produces = "text/plain")
    public String cars() {
        return "Welcome to our fleet REST API! Use /cars for listing and /cars/model/{model} for filtering";
    }

    @RequestMapping(value = "/robots.txt", produces = "text/plain")
    public String robots() {
        return "/backup";
    }
}
