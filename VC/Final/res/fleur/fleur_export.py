
import bpy


bpy.context.scene.frame_set(0)
bpy.ops.export_scene.obj(filepath=(bpy.path.abspath("//normal.obj")))

for i in range(1, 24):
  bpy.context.scene.frame_set(i)
  bpy.ops.export_scene.obj(filepath=(bpy.path.abspath("//running_%.3d.obj" % i)))

 