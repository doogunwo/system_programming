#!/bin/bash
userlist=$(who)
count=$(echo "$userlist" | wc -l)
echo $count