from manim import *

class CreateCircle(Scene):
    def construct(self):
        circle = Circle()  # create a circle
        circle.set_fill(PINK, opacity=0.5)  # set the color and transparency
        self.play(Create(circle))  # show the circle on screen

class SquareToCircle(Scene):
    def construct(self):
        circle = Circle()  # create a circle
        circle.set_fill(PINK, opacity=0.5)  # set color and transparency

        square = Square()  # create a square
        square.rotate(PI / 4)  # rotate a certain amount

        self.play(Create(square))  # animate the creation of the square
        self.play(Transform(square, circle))  # interpolate the square into the circle
        self.play(FadeOut(square))  # fade out animation

class ContinuousMotion(Scene):
    def construct(self):
        func = lambda pos: pos[0]
        stream_lines = StreamLines(func, stroke_width=4, max_anchors_per_line=30)
        self.add(stream_lines)
        stream_lines.start_animation(warm_up=False, flow_speed=1)
        self.wait(stream_lines.virtual_time / stream_lines.flow_speed)

class PointMovingOnShapes(Scene):
    def construct(self):
        square = Square(color=BLUE) # Create a square
        square.flip(RIGHT) # Flip the square to the right
        square.rotate(-3 * TAU / 8) # Rotate the square -3/8 * 2*PI 

         # Play the animation of a square growing from the center
        self.play(GrowFromCenter(square))

class Basic3DExample(ThreeDScene):
    def construct(self):
        cube = Sphere(color='pink')

        self.set_camera_orientation(phi=75 * DEGREES, theta=30 * DEGREES)

        self.play(FadeIn(cube))

        for axis in [RIGHT, UP, OUT]:
            self.play(Rotate(cube, PI / 2, about_point=ORIGIN, axis=axis))

        self.play(FadeOut(cube))

class Rotation3DExample(ThreeDScene):
    def construct(self):
        cube = Cube(side_length=3, fill_opacity=1)

        self.begin_ambient_camera_rotation(rate=0.3)

        self.set_camera_orientation(phi=75 * DEGREES, theta=30 * DEGREES)

        self.play(Write(cube), run_time=2)

        self.wait(3)

        self.play(Unwrite(cube), run_time=2)

class Axes3DExample(ThreeDScene):
    def construct(self):
        axes = ThreeDAxes()

        x_label = axes.get_x_axis_label(Tex("x"))
        y_label = axes.get_y_axis_label(Tex("y")).shift(UP * 1.8)

        # 3D variant of the Dot() object
        dot = Dot3D()

        # zoom out so we see the axes
        self.set_camera_orientation(zoom=0.5)

        self.play(FadeIn(axes), FadeIn(dot), FadeIn(x_label), FadeIn(y_label))

        self.wait(0.5)

        # animate the move of the camera to properly see the axes
        self.move_camera(phi=75 * DEGREES, theta=30 * DEGREES, zoom=1, run_time=1.5)

        # built-in updater which begins camera rotation
        self.begin_ambient_camera_rotation(rate=0.15)

        # one dot for each direction
        upDot = dot.copy().set_color(RED)
        rightDot = dot.copy().set_color(BLUE)
        outDot = dot.copy().set_color(GREEN)

        self.wait(1)

        self.play(
            upDot.animate.shift(UP),
            rightDot.animate.shift(RIGHT),
            outDot.animate.shift(OUT),
        )

        self.wait(2)

class myjob(ThreeDScene):
    def construct(self):
        self.set_camera_orientation(phi = 45*DEGREES, theta = -45*DEGREES)

        axes = ThreeDAxes(y_range=[-3,10,3],y_length=7).add_coordinates()
        
        graph = axes.plot(lambda x : x, x_range=[0,3], color=RED_B)

        area = axes.get_area(graph=graph, x_range=[0,3])

        e=ValueTracker(0)

        surface = always_redraw(
            lambda : Surface(
            lambda u,v : axes.c2p(v, v*np.cos(u), v*np.sin(u)),
            u_range=[0,e.get_value()],
            v_range=[0,3],
            checkerboard_colors={GREEN,PURPLE}
            )
        )

        self.add(axes, surface)
        self.begin_ambient_camera_rotation(rate=PI/15)
        self.play(LaggedStart(Create(surface), Create(area)))
        self.play(
            Rotating(area, axis=RIGHT, radians=2*PI, about_point=axes.c2p(0,0,0)),
            e.animate.set_value(2*PI),
            run_time=6,
            rate_func=linear
            )
        self.stop_ambient_camera_rotation()
        self.wait()

class ParaSurface(ThreeDScene):
    def func_sphere(self, u, v, radius = 1):
        sphereCentre = np.array([0, 0, 0])
        return radius * np.array([np.cos(u) * np.sin(v) - sphereCentre[0]/radius,
                                  np.sin(u) * np.sin(v) - sphereCentre[1]/radius,
                                  np.cos(v) - sphereCentre[2]/radius])

    def construct(self):
        rng = 7
        axes = ThreeDAxes(
            x_range=[-rng, rng], y_range=[-rng, rng], z_range=[-rng, rng],
            x_length=rng, y_length=rng, z_length=rng
            )
        x_label = axes.get_x_axis_label(Tex("x"))
        y_label = axes.get_y_axis_label(Tex("y"))
        z_label = axes.get_z_axis_label(Tex("z"))
        mainSphere = Surface(
            lambda u, v: axes.c2p(*self.func_sphere(u, v, rng)),
            u_range=[0, TAU],
            v_range=[0, TAU],
            resolution=32, fill_opacity=0.1, checkerboard_colors=['#29ABCA', '#236B8E'], stroke_color=BLACK, stroke_width=0.1
        )
        u_sep = ParametricFunction(
            lambda u: (0.5 * 7) * np.array([
                np.cos(u),
                np.sin(u),
                0
            ]), color=RED, t_range = np.array([0, TAU/2, 0.01])
        )
        u_sep.set_z_index(mainSphere.z_index )
        u_sep.rotate(PI / 4, about_point=[0, 0, 0], axis=RIGHT)
        self.set_camera_orientation(theta=70*DEGREES, phi=75*DEGREES)
        self.add(axes, u_sep, mainSphere, x_label, y_label, z_label)