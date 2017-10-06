local TxD = {	
	{0,1,0,1,1,0,1},
	{0,1,1,0,0,0,0},
	{0,0,0,0,0,1,1},
	{0,0,0,1,0,0,0},
	{0,1,1,0,0,0,0},
	{1,0,0,1,0,0,0},
	{0,0,0,0,1,1,0},
	{1,0,0,1,0,0,0}
}

local Q = {0,1/math.sqrt(5),0,0,1/math.sqrt(5),1/math.sqrt(5),1/math.sqrt(5),1/math.sqrt(5)}


function TFN(TxD) -- TFN normált
	local n,m = #TxD,#TxD[1]
	for j=1,m do --D
		local o = 0
		for i=1,n do --T
			o = o + TxD[i][j]^2
		end
		for i=1,n do
			TxD[i][j]=TxD[i][j]/math.sqrt(o)
		end
	end
end

function Cosin(TxD,Q)
	local R = {}
	local n,m = #TxD,#TxD[1]
	for j=1,m do
		local o = 0
		for i=1,n do
			o = o + TxD[i][j]*Q[i] --Skalár szorzás
		end
		R[j]=o
	end
	return R
end

function Dice(TxD,Q)
	local R = {}
	local o = 0
	local n,m = #TxD,#TxD[1]
	for j=1,m do
		local oo = 0
		for i=1,n do
			o = o + TxD[i][j]+Q[i]
		end
		for i=1,n do
			oo = oo + TxD[i][j]*Q[i] --Skaláris szorzás
		end
		R[j]=oo / math.sqrt(o)
	end
	return R
end

function deep_pretty_print(data,szint)
	szint = szint or 0
	local r = ""
	if type(data)=="table" then
		for n,v in pairs(data) do
			local t = ""
			for i=1,szint do t=t.."\t" end
			r = r..t..tostring(n)..":\n"..t..deep_pretty_print(v,szint+1)
		end
	else
		r = "\t"..tostring(data).."\n"
	end
	return r
end

TFN(TxD)
R = {}
R.cos = Cosin(TxD,Q)
R.dice = Dice(TxD,Q)


print(deep_pretty_print(R))





