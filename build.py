import subprocess
import os

if __name__ == "__main__":
    # run make
    #subprocess.run(["bash", "-c", "make"])

    # run exec
    os.chdir("release")
    subprocess.run(["cmd", "/c", "start", "simplecalc.exe"])