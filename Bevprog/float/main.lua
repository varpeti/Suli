alma = {}
korte = {}
alma.ertek = 9
alma.korte = korte
korte.ertek = 10
korte.alma = alma

print(alma.korte.alma.korte.alma.korte.ertek)
print(alma.korte.alma.korte.alma.ertek)
print(korte.alma.korte.alma.korte.alma.ertek)