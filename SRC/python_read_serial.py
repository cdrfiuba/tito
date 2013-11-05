import serial
import sys

valores_anteriores = []
if len(sys.argv) < 2:
	print 'te falta el puerto tty USB, capo'
else:
	print 'abriendo puerto %s' % sys.argv[1]
		
	ser = serial.Serial('/dev/ttyUSB%s' % sys.argv[1], 2400)

	def format_int16(line):
		if len(line) == 2:
			return ord(line[0]) * 256 + ord(line[1])
		else:
			return 'error'
		
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
