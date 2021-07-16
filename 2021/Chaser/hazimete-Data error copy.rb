# -*- coding: utf-8 -*-
require  'CHaserConnect.rb' #呼び出すおまじない

# 書き換えない
target = CHaserConnect.new("Data error")#好きな名前
values = Array.new(10)
random = Random.new # 乱数生成
hoko = 0

def _search(hoko,values,target)
	case hoko
		when 0
			values = target.searchUp
		when 3
			values = target.searchRight
		when 6
			values = target.searchDown
		when 9
			values = target.searchLeft
	end
		return values
end

def _look(hoko,values,target)
	case hoko
		when 0
			values = target.lookUp
		when 3
			values = target.lookRight
		when 6
			values = target.lookDown
		when 9
			values = target.lookLeft
	end
		return values
end
def _aruku(hoko,flag,values,target)

	if flag == 1
		p "flag1"
		return
	end

	case hoko

	when 0
		target.walkUp()

	when 3
		target.walkRight()

	when 6
		target.walkDown()

	when 9
		target.walkLeft()

	end
	return
end

def _kabeyoke(hoko,values)
	loop do
		if hoko == 0
			if values[2] == 2
				hoko =3
			else
				break
			end

		elsif hoko == 3
			if values[6] == 2
				hoko =6
			else
				break
			end

		elsif hoko == 9
			if values[4] == 2
				hoko = 0
			else
				break
			end

		elsif hoko == 6
			if values[8] == 2
				hoko = 9
			else
				break
			end
		end
	end
	return hoko
end

def _enemyCheck(values)

	if values[2] == 1
		return [1,0]
	elsif values[6] == 1
		return [1,3]
	elsif values[8] == 1
		return[1,6]
	elsif values[4] == 1
		return[1,9]
	else
		return[0]
	end
end

def _gettyu(hoko, values,target,flag)
	rand_flag = 0
	if flag == 1
		return 0,rand_flag,hoko
	end
	#アイテムを見つけたら
	if values[2] == 3
 		#詰み要素を見つけたら
 		if values[1] ==2 && values[3] == 2
 		 	values = _look(0, values, target)
 		 	#もし詰み要素を発見したら
 		 	if values[5] == 2
 		 		flag = 1
 		 		hoko = 3
 		 	#無ければ
 		 	else
 		 		flag = 1
 		 		hoko = 0
 		 	end

 		 #安全なら
		else
 		 	hoko = 0
 		end

 	elsif values[6] == 3
 		#詰み要素を見つけたら
 		if values[3] ==2 && values[9] == 2
 		 	values = _look(3, values, target)
 		 	#もし詰み要素を発見したら
 		 	if values[5] == 2
 		 		flag = 1
 		 		hoko = 6
 		 	#無ければ
 		 	else
 		 		flag = 1
 		 		hoko = 3
 		 	end

 		 #安全なら
		else
 		 	hoko = 3
 		end

 	elsif values[8] == 3
 		#詰み要素を見つけたら
 		if values[7] ==2 && values[9] == 2
 		 	values = _look(6, values, target)
 		 	#もし詰み要素を発見したら
 		 	if values[5] == 2

 		 		flag = 1
 		 		hoko = 9
 		 	#無ければ
 		 	else
 		 		flag = 1
 		 		hoko = 6
 		 	end

 		 #安全なら
 		else
 		 	hoko = 6
 		end

 	elsif values[4] == 3
 		#詰み要素を見つけたら
 		if values[1] ==2 && values[7] == 2
 		 	values = _look(9, values, target)
 		 	#もし詰み要素を発見したら
 		 	if values[5] == 2
 		 		flag = 1
 		 		hoko = 0
 		 	#無ければ
 		 	else
 		 		flag = 1
 		 		hoko = 9
 		 	end

 		 #安全なら
 		else
 		 	hoko = 9
 		end

  	end

  	if flag == 1
  		rand_flag = 1
  	end
  	return flag,rand_flag,hoko
end

def _escape(hoko, values,target,flag)
	rand_flag = 0
	if flag == 1
		return 0,rand_flag,hoko
	end
	#敵を見つけたら
	_look(0, values, target)
	flag = 1
 	if values[5] == 1
 		if values[2] ==2 && values[4] == 2
 			flag = 1
 			_look(0,values,target)
 		elsif values[2] ==2 && values[6] == 2
 			flag = 1
 		 	_look(0,values,target)
 		elsif  values[2] == 2
 			flag = 1
 		 	_look(0, values, target)
 		elsif values[4] == 2 && values[6] == 2
 			flag = 1
 			_look(0,values,target)
 		elsif values[4] == 2
 			flag = 1
 			_look(0,values,target)
 		elsif values[6] == 2
 			flag = 1
 			_look(0,values,target)
 		elsif values[1,2,3,4,6,7,8,9] == 0
 			flag = 1
 			_look(0,values,target)
 		elsif values[2] == 2 && values[4] == 2 && values[6] == 2
 			flag = 1
 			putDirection == 0
 		else
 			return hoko,rand_flag,flag
 		end
 		_look(3,values,target)
 		flag = 1
 			if values[2] == 2
 				flag = 1
 				_look(3,values,target)
 			elsif values[2] == 2 && values[6] == 2
 				flag = 1
 				_look(3,values,target)
 			elsif values[6] == 2 && values[8] == 2
 				flag = 1
 				_look(3,values,target)
 			elsif values[6] == 2
 				flag = 1
 				_look(3,values,target)
 			elsif values[8] == 2
 				flag = 1
 				_look(3,values,target)
 			elsif values[2] == 2 && values[8] == 2
 				flag = 1
 				_look(3,values,target)
 			elsif values[1,2,3,4,6,7,8,9] == 0
 				flag = 1
 				_look(3,values,target)
 			elsif values[2] == 2 && values[6] == 2 &&values[8] == 2
 				flag = 1
 				putDirection == 3
			else
 					return hoko,rand_flag,flag
 			end
	_look(9,values,target)
 			if values[2] == 2
 				flag = 1
 				_look(9,values,target)
 			elsif values[2] == 2 && values[4] == 2
 				flag = 1
 				_look(9,values,target)
 			elsif values[2] == 2 && values[8] == 2
 				flag = 1
 				_look(9,values,target)
 			elsif values[4] == 2
 				flag = 1
 				_look(9,values,target)
 			elsif values[8] == 2
 				flag = 1
 				_look(9,values,target)
 			elsif values[4] == 2 && values[8] == 2
 				flag = 1
 				_look(9,values,target)
 			elsif values[1,2,3,4,6,7,8,9] == 0
 				flag = 1
 				_look(9,values,target)
 			elsif values[2] == 2 && values[4] == 2 &&values[8] == 2
 				flag = 1
 				putDirection == 9
			else
 					return hoko,rand_flag,flag
 			end
 	_look(6, values, target)
		flag = 1
 		if values[5] == 1
 		 	if values[2] ==2 && values[4] == 2
 		 	flag = 1
 		 	_look(6,values,target)
 			elsif values[4] ==2 && values[8] == 2
 		 	flag = 1
 		 	_look(6,values,target)
 			elsif  values[2] == 2
 			flag = 1
 		 	_look(6, values, target)
 			elsif values[2] == 2 && values[8] == 2
 			flag = 1
 			_look(6,values,target)
 			elsif values[4] == 2
 			flag = 1
 			_look(6,values,target)
 			elsif values[8] == 2
 			flag = 1
 			_look(6,values,target)
 			elsif values[1,2,3,4,6,7,8,9] == 0
 			flag = 1
 			_look(6,values,target)
 			elsif values[2] == 2 && values[4] == 2 && values[8] == 2
 			flag = 1
 			putDirection == 6
			else
 					return hoko,rand_flag,flag
 			end
 		else
 			_actDirection(hoko,values,target,flag)
		end
	end
		return hoko,rand_flag,flag
end

def _oku(putDirection,target)
	if putDirection == 0
		target.putUp()
	elsif putDirection == 3
		target.putRight()
	elsif putDirection == 6
		target.putDown()
	elsif putDirection == 9
		target.putLeft()
	end
end

def _actDirection(hoko,values,target,flag)
	rand_flag = 0
	# 敵がいるかいないか判断する
	enemy = _enemyCheck(values)
	#もし敵がいたら
	if enemy[0] == 1
		_oku(enemy[1],target)
		flag = 1
	#もし敵がいなかったら
	else
		#アイテムを探し方向を決定する
		flag,rand_flag,hoko = _gettyu(hoko,values,target,flag)
	end
	return flag,rand_flag,hoko
end

#loop do 外変数定義
 count = 0
 rand_flag = 0
 flag = 0
#--------ここから--------
loop do # ここからループ

#---------ここから---------
  values = target.getReady

  if values[0] == 0
    break
  end
#-----ここまで書き換えない-----
puts "first"
p count,rand_flag

if count % 10 == 0 && rand_flag == 0
	hoko = [0,3,6,9].sample()
end

p "second"
p count,rand_flag

if count % 7 == 0 && rand_flag == 0
	p "lookin"
	_look([0,3,6,9].sample(),values,target)
end
#敵を見つけたらPut,又はアイテムを探し動く方向を決める
flag,rand_flag,hoko = _actDirection(hoko, values, target,flag)
#壁があったら避ける
hoko = _kabeyoke(hoko, values)
#決定された方向にWalkする
_aruku(hoko ,flag, values, target)

#カウント変数に+1
count+=1

#---------ここから---------
  if values[0] == 0
    break
  end

end # ループここまで
target.close
#-----ここまで書き換えない-----
