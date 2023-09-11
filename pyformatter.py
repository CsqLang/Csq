import os

"""
install these python modules 
pip install black isort
"""


def format(path):
    for root, dirs, files in os.walk(path):
        for file in files:
            if os.path.splitext(file)[1] != ".py":
                continue
            _file = os.path.join(root, file)
            os.system(f"python3 -m black {_file}")
            os.system(f"python3 -m isort {_file}")


format(".")
