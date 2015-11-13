main = do
	putStrLn $ show(length result) ++ " solutions found!"
	where
		result = place 8
		--调用 place 函数，并用 result 储存结果

place 0 = [[]]
place n = [ q:row | row <- place(n-1) , q <- [1..8] , safe1 q row]
	--输出 List 并过滤掉不符合的情况
safe1 q row = and [not (safe q row i) && not (sameCol q row i) | i <- [0..(length row -1)]]
	--调用函数来判断两种会被攻击到的情况
sameCol q row i = q == row !! i
	--如果在同一行
safe q row i = abs(q - row !! i ) == (i + 1)
	--如果在斜行