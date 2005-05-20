import gamemap
import textfield
import timer
import person


class World:
    def __init__(self, w, h, filename = -1, maps = [3, 3],
                 mapPos = -1):
        self.maps = maps
        self.w = w
        self.h = h
        if mapPos == -1:
            self.mapPos = [maps[0]/2, maps[1]/2]
        else:
            self.mapPos = mapPos
        self.softPos = [self.mapPos[0] * 200, self.mapPos[1] * 200]
        
        self.textField = textfield.Textfield(2, 6, self.w/2 - 5, self.h - 7)
        self.persons = []



        if filename == -1:
            # If no filename is given, I will create an empty world
            self.walkArea = 3
            self.gMaps = []
            for i in range(maps[1]):
                self.gMaps.append([])
            for i in range(maps[0]):
                for j in range(maps[0]):
                    self.gMaps[j].append(gamemap.GameMap(self.w/2 + 2, 6,
                                                         self.w/2 - 5, self.h - 8))
                    self.gMaps[j][i].pos = [(self.mapPos[0] - j) * \
                                            self.gMaps[j][i].size[0],
                                            (self.mapPos[1] - i) * \
                                            self.gMaps[j][i].size[1]]

    def addPerson(self, person):
        person.gMap = self.gMaps[self.mapPos[0]][self.mapPos[1]]
        person.tf = self.textField
        self.persons.append(person)
    
    def resize(self, w, h):
        self.w = w
        self.h = h
        self.textField.resize(self.w/2 - 5, self.h - 7)
        for i in range(self.maps[1]):
            for j in range(self.maps[0]):
                self.gMaps[j][i].resize(self.w/2 + 2, 6,
                                        self.w/2 - 5, self.h - 8)

    def setMapPos(self, x, y):
        for i in range(self.maps[1]):
            for j in range(self.maps[0]):
                self.gMaps[j][i].pos = [-j * self.player.gMap.size[0] + x,
                                        -i * self.player.gMap.size[1] + y]
#        self.mapPos = [x / self.player.gMap.size[0],
#                       y / self.player.gMap.size[1]]
        self.softPos = [x, y]

#        self.mapPos = [(self.player.gMap.size[0] - x) / \
#                    self.player.gMap.size[0],
#                    (self.player.gMap.size[1] - y) / \
#                    self.player.gMap.size[1]]
#        self.softPos = [(self.player.gMap.size[0] - x) % \
#                        self.player.gMap.size[0],
#                        (self.player.gMap.size[1] - y) % \
#                        self.player.gMap.size[1]]
            
    def setPlayer(self, player):
        self.player = player
        player.tf = self.textField
        player.gMap = self.gMaps[self.mapPos[0]][self.mapPos[1]]
        player.say("Ich adde mich!")

    def playerGoRight(self):
        if self.player.pos[0] >= (self.player.gMap.size[1] - 1):
            self.mapPos = [self.mapPos[0] + 1, self.mapPos[1]]
            self.player.gMap = self.gMaps[self.mapPos[0]][self.mapPos[1]]
            self.player.pos[0] -= self.player.gMap.size[0]
            self.textField.sendText("DEBUG: Changed Map")
        if ((self.player.gMap.size[0] * self.mapPos[0] +
             self.player.pos[0]) - self.softPos[0]) > self.walkArea:
            self.setMapPos(self.softPos[0] + 1, self.softPos[1])
        self.player.goRight()

    def playerGoLeft(self):
        if self.player.pos[0] <= 0:
            self.mapPos = [self.mapPos[0] - 1, self.mapPos[1]]
            self.player.gMap = self.gMaps[self.mapPos[0]][self.mapPos[1]]
            self.player.pos[0] += self.player.gMap.size[0]
            self.textField.sendText("DEBUG: Changed Map")
        if ((self.player.gMap.size[0] * self.mapPos[0] +
             self.player.pos[0]) - self.softPos[0]) < -self.walkArea:
            
            self.setMapPos(self.softPos[0] - 1, self.softPos[1])
        self.player.goLeft()
    def playerGoUp(self):
        if self.player.pos[1] <= 0:
            self.mapPos = [self.mapPos[0], self.mapPos[1] - 1]
            self.player.gMap = self.gMaps[self.mapPos[0]][self.mapPos[1]]
            self.player.pos[1] += self.player.gMap.size[1]
            self.textField.sendText("DEBUG: Changed Map")
        if ((self.player.gMap.size[1] * self.mapPos[1] +
             self.player.pos[1]) - self.softPos[1]) < -self.walkArea:
            self.setMapPos(self.softPos[0], self.softPos[1] - 1)
        self.player.goUp()
    def playerGoDown(self):
        if self.player.pos[1] >= (self.player.gMap.size[1] - 1):
            self.mapPos = [self.mapPos[0], self.mapPos[1] + 1]
            self.player.gMap = self.gMaps[self.mapPos[0]][self.mapPos[1]]
            self.player.pos[1] -= self.player.gMap.size[1]
            self.textField.sendText("DEBUG: Changed Map")
        if ((self.player.gMap.size[1] * self.mapPos[1] +
             self.player.pos[1]) - self.softPos[1]) > self.walkArea:
            self.setMapPos(self.softPos[0], self.softPos[1] + 1)
        self.player.goDown()

    def draw(self, dst):
        for elem in self.persons:
            if (self.player.pos[0] == elem.pos[0]) & \
                   (self.player.pos[1] == elem.pos[1]):
                elem.crashWith(elem, self.player)
        self.textField.draw()
        for i in range(self.maps[1]):
            for j in range(self.maps[0]):
                self.gMaps[j][i].draw(dst)
        self.player.draw(dst)
        for elem in self.persons:
            elem.draw(dst)

    def sendText(self, text):
        self.textField.sendText(text)
            
            
