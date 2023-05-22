
import sys
import os
from signal import signal, SIGPIPE, SIG_DFL
signal(SIGPIPE,SIG_DFL)
print("Content-Type: text/plain; charset=utf-8")
print()
# print(sys.stdin.read())
for k, v in os.environ.items():
  print(k, v)
