#! /bin/sh
docker build -t htmltopdf:latest .
fly deploy
