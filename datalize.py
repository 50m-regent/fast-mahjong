import gzip
from defusedxml import ElementTree

def read_mjlog(path):
    with gzip.open(path) as f:
        for line in f:
            tree = ElementTree.fromstring(line)
            
    for i in tree.iter():
        print(i.tag, i.attrib)

if __name__ == '__main__':
    read_mjlog('data/mjlogs/2021111701gm-00e1-0000-0e932974&tw=1.mjlog')