cp grubx64.efi grubx64backup.efi
echo -n -e \\x00 > patch && cat grubx64.efi | strings -t d | grep "Welcome to GRUB!" | awk '{print $1;}' | xargs -I{} dd if=patch of=grubx64.efi obs=1 conv=notrunc seek={}
