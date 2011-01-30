#!/usr/bin/env sh

ID=`id -u`
CONF_DIR="/usr/local/etc/mysqld/webserver"

success()
{
    echo -e "\t[\033[32mSUCCESS\033[0m]"
}

failed()
{
    echo -e "\t[\033[31mFAILED\033[0m]"
    exit 0
}

is_root()
{
    if [ "$ID" != "0" ]; then
        echo -n "/!\ You have to be a root. /!\\"
        failed
    fi
}

setup_dir()
{
    echo -n "*** Set up directories"
    mkdir -p $CONF_DIR && success || failed
}

chmod_dir()
{
    echo -n "*** Chmod directories"
    chmod 777 $CONF_DIR && success || failed
}

is_root
setup_dir
chmod_dir

echo "Done"
