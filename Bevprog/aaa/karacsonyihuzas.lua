NEVEKSZAMA = arg[1] --Ezek a bemenetek 
SEED = arg[2]
ID = arg[3]

if not NEVEKSZAMA then error("Használat: karacsonyihuzas.lua NEVEKSZAMA [SEED, ID]") end
if ID then math.floor(ID) end -- hogy egész szám legyen

function PRNG() -- Pseudorandom szám generálás
	local frand  = assert (io.open ('/dev/urandom', 'rb')) 
	local rand = frand:read(10) -- 10 byte beolvasása
	local x = 0

	for i=1,rand:len() do
		x = x*10 + rand:byte(i)
	end
	return x
end


seed = SEED or PRNG() -- ha nincs bemeneti SEED generál egyet 
math.randomseed(seed) --"random" generelás a seed alapján

kevertnevek = {}
nevek = {}

for i=1,NEVEKSZAMA do
	table.insert(nevek,{i,i}) --számpárok generálása 1-tól NEVEKSZAMA-ig  |pl 1,1 2,2 3,3
end

while (#nevek>0) do --számpárok keverése együtt  |pl 2,2 1,1 3,3 
	local r = math.random(1,#nevek)
	table.insert(kevertnevek,nevek[r])
	table.remove(nevek,r)
end

for i,v in ipairs(kevertnevek) do
	local a
	if i<#kevertnevek then -- számpárok elcsúsztatása  |pl 2,1 1,3 3,2 
		a = kevertnevek[i+1]
	else
		a = kevertnevek[1]
	end
	if not ID then 
		print(v[1],a[2])
	elseif ID == v[1] then
		print(a[2])
	end
end

print(seed)