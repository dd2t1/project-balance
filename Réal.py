import machine
import time
from hx711 import HX711

calibration_factor = 7050  # Ce facteur est obtenu en utilisant le sketch SparkFun_HX711_Calibration

# Définir les broches
DOUT = 1
CLK = 2
BT = 19  # Bouton de tare sur la broche 19
TB = 14  # Nouveau bouton pour lire la valeur du capteur sur la broche 14
MO = 7   # Switch mode
D1 = 1000

# Initialiser le module HX711
hx = HX711(d_out=DOUT, pd_sck=CLK)
hx.set_scale(calibration_factor)
hx.tare()

# Configurer les broches GPIO pour les boutons
btn_tare = machine.Pin(BT, machine.Pin.IN, machine.Pin.PULL_UP)
btn_read = machine.Pin(TB, machine.Pin.IN, machine.Pin.PULL_UP)
switch_mode = machine.Pin(MO, machine.Pin.IN, machine.Pin.PULL_UP)

# Fonction pour enlever les tirets d'une chaîne de caractères
def remove_dashes(s):
    return s.replace('-', '')

# Fonction pour la tare
def tare():
    hx.tare()
    print("Tare activé pour les deux capteurs")
    time.sleep(0.5)  # Petit délai pour éviter les déclenchements multiples

# Fonction pour lire le poids
def read_weight():
    weight = int(hx.get_units())
    result = "{:07d}".format(weight)  # Formater avec 8 chiffres
    result = remove_dashes(result)
    print(result)
    time.sleep(D1 / 1000)  # Délai pour éviter les déclenchements multiples

# Initialisation
print("démarrage")
time.sleep(6)  # Attendre que le capteur soit prêt
hx.tare()
print("mise à zéro")

# Boucle principale
while True:
    # Vérifier si le bouton de tare (BT) est pressé
    if not btn_tare.value():
        tare()
    
    # Vérifier si le bouton de lecture (TB) ou le switch mode (MO) est pressé
    if not btn_read.value() or not switch_mode.value():
        read_weight()

    # Vérifier les commandes série
    if machine.UART(0).any():
        serial_control = input().strip()
        if serial_control == "tare":
            tare()
        else:
            read_weight()

    time.sleep(0.1)  # Boucle principale avec un petit délai
