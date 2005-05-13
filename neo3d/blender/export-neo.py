#!BPY
"""
Name: 'Neo'
Blender: 233
Group: 'Export'
Tip: 'Export to neo file format (.neo3d)'
"""

import Blender
from Blender import NMesh, Object

# get current selected object
mesh_obj = Blender.Object.GetSelected()
if len(mesh_obj) == 0:
	print "Fatal Error: Must select a mesh to output as neo3d"
	print "Found nothing"
	result = Blender.Draw.PupMenu("Select an object to export%t|OK")
	Exit()
if mesh_obj[0].getType() != "Mesh":
	print "Fatal Error: Must select a mesh to output as neo3d"
	print "Found: ", mesh_obj[0].getType()
	result=Blender.Draw.PupMenu("Selected Object must be a mesh to output as MD2?%t|OK")
	Exit()

# mesh data
mesh = mesh_obj[0].getData()
faces = mesh.faces

for elem in faces:
	print
	for i in range(len(elem.v)):
		print "Vertixes: " + str(elem.v[i][0]) + ", " + str(elem.v[i][1]) + \
		      ", " + str(elem.v[i][2])
		if mesh.hasVertexColours():
			col = elem.col[i]
			print "Colors: " + str(col.r) + ", " + str(col.g) + ", " + \
			      str(col.b)

saveFile = file("test.n3d", "w")
saveFile.write("Neo3d Triangle-Object 0.0.1\n");
if mesh.hasVertexColours():
	saveFile.write("vColors\n");

saveFile.write("RawData\n")
for elem in faces:
	if len(elem.v) == 3:
		for i in range(3):
			saveFile.write(str(elem.v[i][0]) + " " + \
				       str(elem.v[i][1]) + " " + \
				       str(elem.v[i][2]) + " ")
			if mesh.hasVertexColours():
				col = elem.col[i]
				saveFile.write(str(float(col.r) / 255.0) + \
					       " " + \
					       str(float(col.g) / 255.0) + \
					       " " + \
					       str(float(col.b) / 255.0) + " ")
	elif len(elem.v) == 4:
		for i in range(3):
			saveFile.write(str(elem.v[i][0]) + " " + \
				       str(elem.v[i][1]) + " " + \
				       str(elem.v[i][2]) + " ")
			if mesh.hasVertexColours():
				col = elem.col[i]
				saveFile.write(str(float(col.r) / 255.0) + \
					       " " + \
					       str(float(col.g) / 255.0) + \
					       " " + \
					       str(float(col.b) / 255.0) + " ")

		for i in [2, 3, 0]:
			saveFile.write(str(elem.v[i][0]) + " " + \
				       str(elem.v[i][1]) + " " + \
				       str(elem.v[i][2]) + " ")
			if mesh.hasVertexColours():
				col = elem.col[i]
				saveFile.write(str(float(col.r) / 255.0) + \
					       " " + \
					       str(float(col.g) / 255.0) + \
					       " " + \
					       str(float(col.b) / 255.0) + " ")

