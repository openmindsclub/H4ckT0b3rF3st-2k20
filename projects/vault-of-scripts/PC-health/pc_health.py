import psutil
import shutil
import os

print("\nCPU : " + str(psutil.cpu_percent(0.1)) + " %")

disk = shutil.disk_usage(os.path.expanduser("~"))
print("\nDisk Usage :\n")
print("TOTAL : {:.2f} GB.".format(disk.total/2**30))
print("USED  : {:.2f} GB.".format(disk.used/2**30))
print("FREE  : {:.2f} GB.".format(disk.free/2**30))

memory = psutil.virtual_memory()
print("\nMemory Usage :\n")

print("TOTAL : {:.2f} GB.".format(memory.total/2**30))
print("USED  : {:.2f} GB.".format(memory.used/2**30))
print("FREE  : {:.2f} GB.".format(memory.free/2**30))
