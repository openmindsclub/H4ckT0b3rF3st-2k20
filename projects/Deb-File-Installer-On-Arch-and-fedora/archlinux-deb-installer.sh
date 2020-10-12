#/bin/bash
mkdir ~/.tmp
cd ~/.tmp
ar x $1
mkdir ~/.tmp/data
cd ~/.tmp/data
tar -xzf ~/.tmp/data.tar.gz
rsync -a ~/.tmp/data/* /
rm -rf ~/.tmp
echo "script finished"
