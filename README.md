git init
git pull https://github.com/Megium/SistemaEragilea

git add .
git commit -m "commitan deskribapena"

git push --set-upstream https://github.com/Megium/SistemaEragilea master
edo
git push -u origin master


EGIN BEHARREKOAK:
	-Aurreko programako quantum denboren funtzioak aldatu. Orain programaren exekuzioarekin funtzionatuko dute.
	-MMU barruko TLB taularen funtzionamendua inplementatu.

	->loader (processG) prozesuak sortzeko eragiketa aldatu, "secondary storage" direktoriotik fitxategiak irakurri eta bertatik informazioa atera dezaten (text, data eta memoria nagusian non dagoen kokatuta.).

	->fitxategitik programa irakurtzeko funtzioa inpementatu. Bertatik beharrezkoak diren informazioak ateratzeko. loader.c fitxategi barruan.