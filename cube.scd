(Material pinkmat
    (color .9 .5 .5)
    (ka .1) (kd .7) (ks .5) (ksp 20) (ksm 0) (kt 0) (ktn 1)
)

(Material redmat
    (color .9 .2 .2)
    (ka .3) (kd .3) (ks 1) (ksp 150) (ksm 1) (kt 0) (ktn 1)
)

(Material blackmat
    (color .2 .2 .9)
    (ka .3) (kd .3) (ks 1) (ksp 150) (ksm 1) (kt 0) (ktn 1)
)

(Material voidmat
    (color  .4 .4 .4)
    (ka .7) (kd .3) (ks 0) (ksp 1) (ksm 1) (kt 0) (ktn 1)
)

(Material greenmat
    (color .4 .8 .2)
    (ka .3) (kd .2) (ks .5) (ksp 100) (ksm 1) (kt 0) (ktn 1)
)

(Material skymat
    (color .2 .5 1)
    (ka .1) (kd .8) (ks .1) (ksp .5) (ksm 1) (kt 0) (ktn 1)
)

(Material sunmat
    (color 1 1 0)
    (ka .1) (kd .8) (ks .1) (ksp .5) (ksm 1) (kt 0) (ktn 1)
)



(Sphere rsph (radius 1.0) (material redmat))
(Sphere psph (radius 1.0) (material pinkmat))
(Sphere bsph (radius 1.0) (material blackmat))
(Sphere vsph (radius 1.0) (material voidmat))
(Sphere gsph (radius 1.0) (material greenmat))
(Sphere ssph (radius 1.0) (material skymat))
(Sphere ysph (radius 1.0) (material sunmat))

(Light amb
    (type 3) (color 1 1 1)
)

(Light dir
    (type 0) (color 1.0 1.0 .7)
)

(Light pt
    (type 1) (color 1.39 1.2 1.0) (falloff .75) (deaddistance .01)
)

(Light sunlt
    (type 1) (color 1.39 1.2 1.0) (falloff 1.2) (deaddistance .01)
)


(Camera cam
    (perspective 1)
    (l -.334) (r .334) (b -.334) (t .334) (n 1) # no far plane 
)

(G xStrip
	(I s1 rsph (T -2 0 0))
	(I s2 bsph (T 0 0 0))
	(I s3 gsph (T 2 0 0))
)

(G horizontalLayer
	(I l1 xStrip (T 0 0 2))
	(I l1 xStrip (T 0 0 0))
	(I l1 xStrip (T 0 0 -2))
)

(G cube
	(I c1 horizontalLayer (T 0 2 0))
	(I c1 horizontalLayer (T 0 0 0))
	(I c1 horizontalLayer (T 0 -2 0))
)


(G scene
(I cam1 cam)
   (I dir1 dir (Xform       -.9304  0  .3665 0
                            .1444  -.9191  .3665 0
                            .3369  .3939 .8552 0
                            0  0   0 1)) # points toward (.5,.5,-.5)
   (I amb1 amb)
   (I pt1 pt (T 5 5 -5))
   (I pt1 pt (T -5 -12 -5))
	(I background vsph (S 2000 2000 .1) (T 0 0 -15))
   	(I test cube (S .5 .5 .5)(R -45 1 .5 1)(T 0 0 -10))
(I sl sunlt (T 5 5 19))
)

(Render scene)


