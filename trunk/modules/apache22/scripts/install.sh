#!/usr/bin/env sh

CONF_DIR="/usr/local/etc/apache22/escienta"

success()
{
    echo -e "\t[\033[32mSUCCESS\033[0m]"
}

failed()
{
    echo -e "\t[\033[31mFAILED\033[0m]"
    exit 0
}

setup_dir()
{
    echo -n "*** Set up directories"
    mkdir -p $CONF_DIR && success || failed
}

setup_dir

echo "Done"
