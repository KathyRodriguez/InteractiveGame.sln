using System;
using System.Drawing;
using System.Windows.Forms;

class InteractiveGame : Form
{
    private int score = 0;
    private int speed = 10;
    private int x = 0;
    private int y = 0;
    private int targetX;
    private int targetY;
    private bool hit = false;

    public InteractiveGame()
    {
        Text = "Interactive Game";
        Size = new Size(600, 400);
        DoubleBuffered = true;
        targetX = ClientSize.Width / 2;
        targetY = ClientSize.Height / 2;
        Timer timer = new Timer();
        timer.Interval = 1000 / 60;
        timer.Tick += OnTick;
        timer.Start();
        MouseDown += OnMouseDown;
    }

    private void OnTick(object sender, EventArgs e)
    {
        if (!hit)
        {
            x += (targetX - x) / speed;
            y += (targetY - y) / speed;
        }

        Invalidate();
    }

    private void OnMouseDown(object sender, MouseEventArgs e)
    {
        if (Math.Abs(e.X - x) < 50 && Math.Abs(e.Y - y) < 50)
        {
            score++;
            speed += 2;
            hit = true;
        }
        else
        {
            score--;
            speed -= 2;
            hit = false;
        }

        targetX = e.X;
        targetY = e.Y;
    }

    protected override void OnPaint(PaintEventArgs e)
    {
        Graphics g = e.Graphics;
        g.Clear(Color.White);
        g.FillEllipse(Brushes.Red, x - 25, y - 25, 50, 50);
        g.DrawString("Score: " + score, Font, Brushes.Black, 10, 10);
    }

    static void Main()
    {
        Application.Run(new InteractiveGame());
    }
}
