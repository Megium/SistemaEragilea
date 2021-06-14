git init
git pull https://github.com/Megium/SE_proiektua

git add .
git commit -m "commitan deskribapena"

git push --set-upstream https://github.com/Megium/SE_proiektua master
edo
git push -u origin master


EGIN BEHARREKOAK:
	-Aurreko programako quantum denboren funtzioak aldatu. Orain programaren exekuzioarekin funtzionatuko dute.
	-MMU barruko TLB taularen funtzionamendua inplementatu.
	-Memoria birtuala sortu, eta ulertu.
	-Orri taularen funtzioa sortu.

	->pcb estrukturako aldagaiak aldatu behar dira, orain ausaz sortu beharrean fitxategitik atera beharko ditu.

	->loader (processG) prozesuak sortzeko eragiketa aldatu, "secondary storage" direktoriotik fitxategiak irakurri eta bertatik informazioa atera dezaten (text, data eta memoria nagusian non dagoen kokatuta.).

	->fitxategitik programa irakurtzeko funtzioa inpementatu. Bertatik beharrezkoak diren informazioak ateratzeko. loader.c fitxategi barruan.

	->fitxategia irakurtzeko funtzioak datuak "memorian" gorde eta kokapena gorde. Exekuzioa hastean memoriara jo eta 