import serial
import sys
import platform

valores_anteriores = []
if len(sys.argv) < 2:
    print 'te falta el puerto tty USB, capo'
else:
    print 'abriendo puerto %s' % sys.argv[1]
        
    if platform.system() == "Linux":
        ser = serial.Serial('/dev/ttyUSB%s' % sys.argv[1], 2400)
    elif platform.system() == "Windows":
        ser = serial.Serial('COM%s' % sys.argv[1], 2400, timeout=1)
        
    if sys.argv[2] == "printf":
        while(1):
            print ser.readline()[:-1]
        sys.exit()
        
    try:
        values = []
        while(1):
            values.append(ser.read())
            if ord(values[-1]) == 255:
                ultimo_valor = format_int16(values[0:2])
                print ultimo_valor
                if ultimo_valor != 'error':
                    valores_anteriores.append(ultimo_valor)
                values = []
    except:
        print "\nmax: %i, min: %i avg: %i" % (max(valores_anteriores), min(valores_anteriores), sum(valores_anteriores) / len(valores_anteriores))
        sys.exit()

def format_int16(line):
    if len(line) == 2:
        return ord(line[0]) * 256 + ord(line[1])
    else:
        return 'error'
        