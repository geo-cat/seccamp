require 'socket'

loop do
port = if ARGV[0] then ARGV[0] else 'echo' end
gate = TCPServer.open(port)

sock = gate.accept
gate.close
 
while msg = sock.gets
	sock.write(msg)
	print("you get:", msg)

end
sock.close
end
