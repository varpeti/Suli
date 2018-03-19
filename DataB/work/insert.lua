math.randomseed(3773)

local function randUPch()
    return string.char( math.random(65,90) )
end

local function randLOch()
    return string.char( math.random(97,122) )
end

local function randtext(num)
    local text = ""
    if math.random(0,1)==1 then text = text .. randUPch()
    else text = text .. randLOch(); end
    local i = -3
    while (i<0 or math.random(0,3)~=1 ) do
        if math.random(10)==1 then text = text .. randUPch()
        else text = text .. randLOch() end
        i=i+1
        if i>4 then break end
    end

    if (num==1 and text:len()<8 ) then 
        while (math.random(0,2)~=1) do
            text = text..math.random(0,9)
        end
    end
    return text
end

local function randname()
    return randtext(math.random(1))
end

--Admin, Log
for i=1,10 do
    local name = randname()
    local lvl = 7-(i>6 and 7 or i)
    print([[insert into AbsUser values (']]..name..[[',']]..math.random(0,9999999999)..math.random(0,9999999999)..[[');]] )
    print([[insert into Admin values (']]..name..[[',']]..lvl..[[');]] )
    print([[insert into Log values (']]..name..[[',']]..name..[[ created.');]] )
end

--User, UserWall
for i=1,100 do
    local name = randname()
    print([[insert into AbsUser values (']]..name..[[',']]..math.random(0,9999999999)..math.random(0,9999999999)..[[');]] )
    print([[insert into User2 values (']]..name..[[',sysdate);]] )
    print([[insert into UserWall values (']]..name..[[');]] )
end




