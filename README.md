# Authentification-System
The Authentification System project in CSE201.
The project is about developping an app that will use facial recognition securely and efficiently.

## Members (name surname, github username, trello username, [role])

    - Paula Gonzalez Alvarez, gonzalezpaula, paula_gonzalez
    - Alexandru Serban, alexserban2002, alexandruserban19
    - Bach Khoa Do, DoBachKhoa, bachkhoado1
    - Bogdan Budura, JohnnyVenturas, bogdanbudura, compilation leader
    - Cezara Petrui, cezarapetrui19, cezarapetrui
    - Francisco Moreira Machado Neto, fcomoreira1, franciscomoreiramachadoneto, project leader
    - Jasmine Watissee, jasminewatissee, jasminewatissee1
    - Mija Pilkaite, mija-pilkaite, mijapilkaite
    - Romain Poggi, rompoggi, romainpoggi
    - Santorin Yu, SantorinYu01, santorinyu
    - Simon Sebastian Mihai, sebiinfo, simonsebastianmihai, github leader
    - Sophie-Claire Antoun, sophieantoun, sophieclaireantoun
    - Victor Lasocki, victor-lasocki, victorlasocki
    - Yassine Turki, yassine-turki, turkiyassine2, trello leader

## Teams

### Machine Learning Implementation and Facial Recognition

    - Alexandru Serban
    - Bach Khoa Do
    - Bogdan Budura
    - Cezara Petrui
    - Francisco Moreira Machado Neto
    - Romain Poggi
    - Santorin Yu
    - Simon Sebastian Mihai

### Password encryption and Image Encoding

    - Mija Pilkaite
    - Sophie-Claire Antoun
    - Yassine Turki
    - Jasmine Watissee
    
### Setting up database
    
    - Mija Pilkaite
    - Sophie-Claire Antoun

### User interface
    
    - Paula Gonzalez Alvarez
    - Victor Lasocki

### Running the code
    
    -For Linux and MacOS operating systems
    mkdir build 
    cd build 
    cmake .. 
    cmake --build .  
    ./AuthentificationSystem 

    Instead of using cmake --build . one can use:
    make -j 8 (or 12 16 32 i.e number of cores you have on your machine)
    This is to speed up compilation on the first build. Use only on the first 
    build!
    
    Keep in mind that for the program to work properly you need to register
    at least three faces. Not doing so can result in bugs. 
    After each register it is recommended to close and reopen the program to prevent 
    any bugs.

    Enjoy :) 
