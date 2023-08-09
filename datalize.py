import gzip
from defusedxml import ElementTree

class MjlogReader:
    IGNORE_TAGS = [
        'mjloggm',
        'SHUFFLE',
        'GO',
        'UN',
        'BYE',
        'TAIKYOKU'
    ]
    
    def __init__(self, path):
        with gzip.open(path) as f:
            for line in f:
                self.tree = ElementTree.fromstring(line)
                
    def init(self, attrib):
        print('init', attrib)
    
    def reach(self, attrib):
        print('reach', attrib)
        
    def n(self, attrib):
        print('n', attrib)
        
    def dora(self, attrib):
        print('dora', attrib)
        
    def agari(self, attrib):
        print('agari', attrib)
        
    def ryuukyoku(self, attrib):
        print('ryuukyoku', attrib)
        
    def draw(self, tag):
        print('draw', tag)
        
    def discard(self, tag):
        print('discard', tag)
        
    def analyze(self):
        for i in self.tree.iter():
            if i.tag in MjlogReader.IGNORE_TAGS:
                continue
            
            if 'INIT' == i.tag:
                self.init(i.attrib)
            elif 'REACH' == i.tag:
                self.reach(i.attrib)
            elif 'N' == i.tag:
                self.n(i.attrib)
            elif 'DORA' == i.tag:
                self.dora(i.attrib)
            elif 'RYUUKYOKU' == i.tag:
                self.ryuukyoku(i.attrib)
            elif 'AGARI' == i.tag:
                self.agari(i.attrib)
            elif i.tag[0] in 'TUVW':
                self.draw(i.tag)
            elif i.tag[0] in 'DEFG':
                self.discard(i.tag)
    

if __name__ == '__main__':
    path = 'data/mjlogs/2021111701gm-00e1-0000-0e932974&tw=1.mjlog'
    
    reader = MjlogReader(path)
    reader.analyze()