import gzip
from defusedxml import ElementTree

class State:
    @classmethod
    def id2onehot(cls, tile):
        result = [0] * 34
        result[tile // 4] = 1
        
        return result
    
    def __init__(self):
        self.bonus_tiles = [0] * 5
    
    def __str__(self):
        return \
            '-----------------------\n' + \
            f'Round: {self.round}, Stack: {self.stack}, Bet: {self.bet}, Bonus: {self.bonus_tiles}, Oya: {self.oya}, Score: {self.scores}\n' + \
            f'Hand: {self.hands}'

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
                
        self.state = State()
                
    def init(self, attrib):
        self.state.round, self.state.stack, self.state.bet, _, _, bonus_tile = eval(attrib['seed'])
        self.state.bonus_tiles[0] = bonus_tile // 4
        
        self.state.scores = eval(attrib['ten'])
        
        self.state.oya = int(attrib['oya'])
        
        self.state.hands = [
            [tile // 4 for tile in eval(attrib['hai0'])],
            [tile // 4 for tile in eval(attrib['hai1'])],
            [tile // 4 for tile in eval(attrib['hai2'])],
            [tile // 4 for tile in eval(attrib['hai3'])]
        ]
    
    def reach(self, attrib):
        print('reach', attrib)
        
    def n(self, attrib):
        pass
        
    def dora(self, attrib):
        pass
        
    def agari(self, attrib):
        pass
        
    def ryuukyoku(self, attrib):
        pass
        
    def draw(self, tag):
        pass
        
    def discard(self, tag):
        pass
        
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
                
            # print(self.state)
    

if __name__ == '__main__':
    path = 'data/mjlogs/2021111701gm-00e1-0000-0e932974&tw=1.mjlog'
    
    reader = MjlogReader(path)
    reader.analyze()