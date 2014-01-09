#---------------------------------
# INITIALISATION DES VARIABLES 
#---------------------------------

# Indiquer le compilateur
CC= gcc

# Les chemins ou se trouvent les fichiers a inclure
INCLUDE= -I/usr/include

# Options de compilation.
CFLAGS=  $(INCLUDE) -c -Wno-deprecated

# Les chemins ou se trouvent les librairies
LIBRARY_PATH= -L/usr/lib

# Options pour le linker.
LDFLAGS= $(LIBRARY_PATH) -o

# Les librairies avec lesquelle on va effectueller l'edition de liens
LIBS=  

# Les fichiers sources de l'application
FILES= main.c anneauCircu.c Composant.c FactoryProduit.c FactoryRobot.c Operation.c PileFIFO.c ProducteurComposant.c Produit.c Robots.c SortieProduit.c voidBuf.c

#-----------
# LES CIBLES
#-----------
lo41 :  $(FILES:.c=.o)
	$(CC) $(LDFLAGS) lo41 $(FILES:.c=.o) $(LIBS)

.PHONY : clean
clean:
	/bin/rm $(FILES:.c=.o) lo41

#-----------------------------------------------------------------------------
# LES REGLES DE DEPENDANCE. Certaines sont implicites mais je recommande d'en 
# mettre une par fichier source. 
#-----------------------------------------------------------------------------
main.o:main.c anneauCircu.c anneauCircu.h FactoryProduit.h ProducteurComposant.h SortieProduit.h
anneauCircu.o:Robots.h Produit.h ProducteurComposant.h
FactoryProduit.o:Produit.h Composant.h Operation.h
FactoryRobot.o:Robots.h
Produit.o:PileFIFO.h

#---------------------------------
# REGLES DE COMPILATION IMPLICITES
#---------------------------------
%.o : %.c ; $(CC) $(CFLAGS) $*.c

