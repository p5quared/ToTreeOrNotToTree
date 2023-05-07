#! /bin/sh
docker build -t pdfconverter:latest .
# shellcheck disable=SC2046
docker kill $(docker ps -q)
docker run -p 8080:8080 pdfconverter:latest

