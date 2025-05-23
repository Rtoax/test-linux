#!/bin/bash

admin_users=( $(sudo groupmems --group wheel --list) )

echo wheel: ${admin_users[@]}
