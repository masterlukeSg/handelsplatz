# Handelsplatz


### Arbeitsaufteilung

- Nutzer Klasse: Aicha
- Handelsguter Klasse : Aicha
- Marketplace: Imene & Lukas

- Server: Aicha & Lukas
- Client: Imene & Lukas

# Klassenbeschreibung

## Nutzerklasse

```
Die Klasse dient dazu den Benutzername, Kontostand und das Passwort zurückzugeben.
Der Kontostand kann angepasst werden, es kann überprüft werden ob der Nutzer bestimmte Handelsgüter besitzt und kann vorhandene Handelsgüter hinzufügen und entfernen
```

## Handelsguter

```
Die Klasse ist dafür da, um einzelne Objekte zu erzeugen. Die bekommen beim erstellen einnen Namen, sowie die Anzahl an vorhandenen Handelsguteren.
Man kann die Anzahl der Handelsguter bearbeiten und sich zurückzugeben lassen. Der Name des Handelsguts ist auch wiedergebbar. 
```

## Marketplace

```
Die Klasse ist das Herzstück für unser Handelsplatz. Die Klasse bietet alle Funktionen an, um mit dem Marketplace selber zu handel, oder auch angebote aufzugeben und angebote von anderen Nutzer anzunehmen. 
Durch die login und register Funktionen hat jeder Nutzre sein eigenes Konto und kann nur auf sein Account zugreifen.
```


## Start Projekt

1.  cmake -S . -B build && cmake --build build && --install build 
2.  cd extra: uvicorn server:app --reload --port 8000
3.  python3 client.py


## Download Projekt
```
cd existing_repo
git remote add origin https://gitlab.informatik.uni-bonn.de/baumeisterl0/handelsplatz.git
git branch -M main
git push -uf origin main
```
