package main 

import (
	"net/http"
	"log"
	"fmt"
	"io/ioutil"
)

var (
	flag []byte
	html []byte
	err error = nil
)

func handler(w http.ResponseWriter, r *http.Request) {
	w.Header().Add("X-IftaCTF-16-flag", string(flag))
	fmt.Fprintf(w, string(html))
}

func init() {
	flag, err = ioutil.ReadFile("flag.txt")
	if err != nil {
		log.Fatal(err)
	}
	html, err = ioutil.ReadFile("index.html")
	if err != nil {
		log.Fatal(err)
	}
}

func main() {
	http.HandleFunc("/", handler)
	log.Fatal(http.ListenAndServe(":4006", nil))
}
