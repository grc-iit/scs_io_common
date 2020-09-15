#! /usr/bin/env bash


# cmd :  bash usage_example.sh --config=./conf.config    

source ./bash-ini-parser

CONFIG=$(args_parser "$@")

cfg_parser "$CONFIG"
cfg_section_general  # general is a section in the config file [general]  <- like so
echo $testkey   # testkey is the name of the key
