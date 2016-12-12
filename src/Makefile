#
# Makefile
# 

CC=g++
LIB_DIR=./lib
INC_DIR=./include
BIN_DIR=./bin
SRC_DIR=./src
SRC_DIR_INC=./src_inc

all:
	$(CC) -o main $(SRC_DIR_INC)dSFMT.c $(SRC_DIR)main.cpp -lGL -lglut -lGLU -I$(INC_DIR) -msse2 -DDSFMT_MEXP=2203 -DHAVE_SSE2 -std=c++11