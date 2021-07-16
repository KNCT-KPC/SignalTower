import random
import pyxel
wh = 120#画面たかさ
ww = 160#画面横幅
ph = 14#プレイヤーのたかさ
pw = 10#プレイヤー横幅

class Vec2:
    def __init__(self, x, y):
        self.x = x
        self.y = y
class Bard:
    def __init__(self):
        self.pos = Vec2(0, 0)
        self.vec = 0
        self.speed = -0.75
    def update(self, x, y, dx):
        self.pos.x = x
        self.pos.y = y
class Slime:#JUMPする
    def __init__(self):
        self.pos = Vec2(0, 0)
        self.vec = 0
        self.speed = -0.75
        self.Gy = 100
        self.pos.y = self.Gy
        self.vy = 0
        self.gy = 0.05
        self.jump = False
    def update(self, x, y, dx):
        self.input_key()
        self.vy += self.gy
        self.pos.x = x
        self.pos.y += self.vy
        if self.pos.y > self.Gy - 8:
            self.pos.y = self.Gy - 8
            self.jump = False
    def input_key(self):
        if pyxel.btnp(pyxel.KEY_J):
            if self.jump == False:
                self.vy = -1.8
                self.jump = True
class Bomb:#爆弾
    def __init__(self):
        self.pos = Vec2(0, 0)
        self.vec = 0
        self.speed = -0.25
    def update(self, x, y, dx):
        self.pos.x = x
        self.pos.y = y
class Brave:#高速トリ
    def __init__(self):
        self.pos = Vec2(0, 0)
        self.vec = 0
        self.speed = -1.2
    def update(self, x, y, dx):
        self.pos.x = x
        self.pos.y = y
class Ball:
    def __init__(self):
        self.pos = Vec2(0, 0)
        self.vec = 0
        self.size = 2
        self.speed = 2
        self.color = 8
 
    def update(self, x, y,dx, size, color):
        self.pos.x = x
        self.pos.y = y
        self.size = size
        self.color = color
class App:
    gy = 100
    def __init__(self):
        pyxel.init(160,120,caption="jump_game",fps=100)#1s=100F
        self.init()
        self.score = 0
        self.highscore = 0
        self.bombnum = 0
        self.count = [2,3,4,5]
        self.appear = [1,1,1,2,2,3,3,4]
        self.enemy = 0
        self.Balls = []
        self.Bards = []
        self.Slimes = []
        self.Bombs = []
        self.Braves = []
        self.peaples = []
        self.barrier = False
        self.game_over = False
        self.move = True
        pyxel.run(self.update,self.draw)
        
    def init(self):
        pyxel.load("my_resource.pyxres")
        self.x = ww/6
        self.y = self.gy - 16
        
    def update(self):
        if pyxel.btnp(pyxel.KEY_SHIFT):#後で消すかも
            self.game_over = True
            self.move = False
            
        if self.score == self.highscore + 1:#ハイスコア更新
            self.highscore += 1

        if self.game_over:#game over
            if self.highscore <= self.score:
                self.highscore = self.score
            self.score = 0
            self.bombnum = 0
            self.move = False
            
            if pyxel.btnp(pyxel.KEY_ENTER):#コンテニュー
                 self.game_over = False
                 self.move = True
                       
        if pyxel.frame_count % 100 == 0 and 20 > self.score >= 10 and self.move:#ランダムで敵出したい1
            self.enemy = random.choices(self.appear)
            
        if pyxel.frame_count % 50 == 0 and self.score > 20 and self.move:#ランダムで敵出したい2
            self.enemy = random.choices(self.appear)
            
        if ((pyxel.frame_count % 250 == 0 and pyxel.frame_count != 0 and pyxel.frame_count != 0 and self.score < 10)
                    or (self.score >= 10 and self.enemy == [1] and pyxel.frame_count % 100 == 0) and self.move):#とり
                new_bard = Bard()
                new_bard.update(ww,self.y,new_bard.vec)
                self.Bards.append(new_bard)
                if self.score >= 20:
                    new_bard.speed *= self.score / 20
                
        bamo= len(self.Bards)
        for t in range(bamo):#bardだす
            if 0 < self.Bards[t].pos.x and self.Bards[t].pos.x <= ww and self.move:
                    self.Bards[t].update(self.Bards[t].pos.x + self.Bards[t].speed, 
                                        self.Bards[t].pos.y,self.Bards[t].vec)
            else:
                del self.Bards[t]
                break     
            if self.x + pw > self.Bards[t].pos.x + 16 and self.barrier == False:#bardに1P当たったらgame_over
                self.game_over = True


        if ((pyxel.frame_count % 450 == 0 and 10 > self.score >= 2) or
                (self.score >= 10 and self.enemy == [2] and pyxel.frame_count % 75 == 0) and self.move):#スライム
                new_slime = Slime()
                new_slime.update(ww,new_slime.pos.y,new_slime.vec)
                self.Slimes.append(new_slime)
                if self.score >= 20:
                    new_slime.speed *= self.score / 20
                
        slmo= len(self.Slimes)
        for s in range(slmo):#通過します
            if 0 < self.Slimes[s].pos.x + 8 and self.Slimes[s].pos.x <= ww and self.move:
                    self.Slimes[s].update(self.Slimes[s].pos.x + self.Slimes[s].speed, 
                                        self.Slimes[s].pos.y,self.Slimes[s].vec)
            else:
                self.score += 1
                del self.Slimes[s]
                break     
            if ((self.x + pw >= self.Slimes[s].pos.x >= self.x  or self.x + pw >= self.Slimes[s].pos.x + 8 >= self.x)
                        and self.y + 16 >= self.Slimes[s].pos.y >= self.y and self.barrier == False):#slimeに1P当たったらgame_over
                self.game_over = True

        if ((pyxel.frame_count % 550 == 0 and 10 > self.score >= 5) or (self.score >= 10 and self.enemy == [3] and pyxel.frame_count % 50 == 0)
                    and self.bombnum == 0 and self.move):#爆弾
            self.bombcount = random.choice(self.count)
            new_bomb = Bomb()
            new_bomb.update(ww,self.y,new_bomb.vec)
            self.Bombs.append(new_bomb)
            self.bombnum = 1
            if self.score >= 20:
                    new_bomb.speed *= self.score / 20
            
        bommo= len(self.Bombs)
        for b in range(bommo):#bombだす
            if 0 < self.Bombs[b].pos.x and self.Bombs[b].pos.x <= ww and self.bombcount != 0 and self.move:
                    self.Bombs[b].update(self.Bombs[b].pos.x + self.Bombs[b].speed, 
                                        self.Bombs[b].pos.y,self.Bombs[b].vec)       
            else:
                self.score += 1
                self.bombnum = 0
                del self.Bombs[b]
                break     
            if self.x + pw >= self.Bombs[b].pos.x  and self.barrier == False:#bombに1P当たったらgame_over
                self.game_over = True

        if ((pyxel.frame_count % 500 == 0 and 10 > self.score >= 5) or
                    (self.score >= 10 and self.enemy == [4] and pyxel.frame_count % 100 == 0)and self.move):#brave
                    new_brave = Brave()
                    new_brave.update(ww,self.y,new_brave.vec)
                    self.Braves.append(new_brave)
                    if self.score >= 20:
                        new_brave.speed *= self.score / 20
                    
        bramo= len(self.Braves)
        for f in range(bramo):#braveだす
            if 0 < self.Braves[f].pos.x + 16 and self.Braves[f].pos.x <= ww and self.move:
                    self.Braves[f].update(self.Braves[f].pos.x + self.Braves[f].speed, 
                                        self.Braves[f].pos.y,self.Braves[f].vec)
            else:
                del self.Braves[f]
                break     

        if pyxel.btnp(pyxel.KEY_F) and len(self.Balls) < 1 and self.move:#たま
            new_ball = Ball()
            new_ball.update(self.x + 13,self.y + 7, 
                                new_ball.vec, new_ball.size, new_ball.color)
            self.Balls.append(new_ball)
            if self.score >= 20:
                new_ball.speed *= self.score / 20
 
        ball_count = len(self.Balls) #ballだす
        flag = 0
        for i in range(ball_count):
            if 0 < self.Balls[i].pos.x and self.Balls[i].pos.x < ww  and self.move:
                    self.Balls[i].update(self.Balls[i].pos.x + self.Balls[i].speed,
                                        self.Balls[i].pos.y,
                                        self.Balls[i].vec, self.Balls[i].size, self.Balls[i].color)
            else:
                del self.Balls[i]
                break

            for b in range(bommo):  #bomb当てたとき
                 if self.Bombs[b].pos.x <= self.Balls[i].pos.x:
                     self.bombcount -= 1
                     del self.Balls[b]
                     flag = 1
                     break
            if flag == 0:
                for t in range(bamo):  #ball当てたら加点
                    if self.Bards[t].pos.x <= self.Balls[i].pos.x:
                        self.score += 1
                        del (self.Bards[t],self.Balls[i])
                        break
                               
    def draw(self):
        if self.game_over:
            pyxel.cls(3)
            pyxel.text(ww/2 - 25,wh/2 -10," GAME OVER\nRETRY:ENTER",0)
        if self.game_over == False:
            pyxel.cls(11)#背景
            pyxel.rect(0,self.gy,pyxel.width,pyxel.height,3)#床
            pyxel.blt(self.x,self.y,0,0,0,12,16,0)#blt(描写する座標,始めのx,y,たてよこ,透過する色)
            pyxel.text(self.x/10,self.y/7,"HIGH SCORE " + str(self.highscore),8)
            pyxel.text(self.x/10,self.y/7,"\nSCORE      " + str(self.score),8)
            pyxel.text(self.x/10,self.y/2.5,"SHOOT: F\nJUMP:  J",1)
            
            for ball in self.Balls:#ball
                    pyxel.circ(ball.pos.x,ball.pos.y,ball.size,ball.color)
                    
            for bard in self.Bards:#Bard
                    pyxel.blt(bard.pos.x,bard.pos.y,0,32,0,16,16,0)
            for slime in self.Slimes:#slime
                    pyxel.blt(slime.pos.x,slime.pos.y,0,16,8,8,8,0)
            for bomb in self.Bombs:#bomb
                    pyxel.blt(bomb.pos.x,bomb.pos.y,0,16,16,16,16,10)
                    pyxel.text(bomb.pos.x + 7,bomb.pos.y + 6, str(self.bombcount),8)
            for brave in self.Braves:#Brave
                    pyxel.blt(brave.pos.x,brave.pos.y,0,32,16,16,16,0)

App()