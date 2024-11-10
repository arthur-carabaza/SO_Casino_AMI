using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace WindowsFormsApplication1
{

        public partial class Form1 : Form
        {
            Socket server;
            bool conectado = false;
            Thread atender;

            public Form1()
            {
                InitializeComponent();
                CheckForIllegalCrossThreadCalls = false;
            }

            private void Form1_Load(object sender, EventArgs e)
            {
                // Establecer los colores iniciales de los botones
                conectar.BackColor = Color.Red; // Color rojo para el botón conectar
                conectar.ForeColor = Color.White;

                desconectar.BackColor = Color.Black; // Color negro para el botón desconectar
                desconectar.ForeColor = Color.White;
                this.Paint += new PaintEventHandler(Form1_Paint);
            }

            private void Form1_Paint(object senser, PaintEventArgs e)
            {
                Graphics g = e.Graphics;
                Brush brush = conectado ? Brushes.Green : Brushes.Red; // Verde si está conectado, rojo si no
                g.FillEllipse(brush, new Rectangle(20,20,20,20)); // Dibujar el círculo en la esquina superior izquierda
            }
            private void AtenderServidor()
            {
                while (true)
                {
                    byte[] msg2 = new byte[80];
                    server.Receive(msg2 );
                    string[] trozos = Encoding.ASCII.GetString(msg2).Split('/');
                    int codigo = Convert.ToInt32(trozos[0]);
                    string mensaje = trozos[1].Split('\0')[0];


                    switch (codigo)
                    {

                        case 1:
                            MessageBox.Show(mensaje);
                            label3.Text = nombre.Text;
                            break;
                        case 2:
                            MessageBox.Show(mensaje);

                            break;
                        case 3:
                            MessageBox.Show(mensaje);
                            break;
                        case 4:
                            MessageBox.Show(mensaje);
                            break;
                        case 5:
                            MessageBox.Show(mensaje);
                            break;
                        case 6:
                            string aux="";
                            for(int i = 2; i < trozos.Length; i++)
                                aux = aux + trozos[i] + "\n";
                            LbLcon.Text = aux;
                            break;


                    }
                }
            }
            private void conectar_Click(object sender, EventArgs e)
                {
                    //Creamos un IPEndPoint con el ip del servidor y puerto del servidor 
                    //al que deseamos conectarnos
                    IPAddress direc = IPAddress.Parse("192.168.56.101");
                    IPEndPoint ipep = new IPEndPoint(direc, 50003);


                    //Creamos el socket 
                    server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                    try
                    {
                        server.Connect(ipep);//Intentamos conectar el socket

                        conectado = true;
                        this.Invalidate(new Rectangle(20,20,20,20)); //Redibujamos el forms para actiualizar el circulo 
                        this.Update();

                        MessageBox.Show("Conectado");
                    }

                    catch (SocketException )
                    {
                        //Si hay excepcion imprimimos error y salimos del programa con return 
                        MessageBox.Show("No he podido conectar con el servidor");
                        return;
                    }
                    ThreadStart ts = delegate { AtenderServidor(); };
                    atender = new Thread(ts);
                    atender.Start();
                }

                private void button2_Click(object sender, EventArgs e)
                {
            
                    if (Dinero.Checked)
                    {
                        //Quiere saber cuanto dinero tiene
                        string mensaje = "3/" + nombre.Text;
                        try
                        {
                            // Enviamos al servidor el nombre tecleado
                            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                            server.Send(msg);

                        }
                        catch (Exception ex)
                        {
                            MessageBox.Show("Error al realizar la peticion, asegurese de estar conectado");
                        }
                    }
                    else if (Victorias.Checked)
                    {
                        //Quiere saber cuantas victoras tengo
                        string mensaje = "4/" + nombre.Text;
                        // Enviamos al servidor el nombre tecleado
                        byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                        server.Send(msg);

                    }
                    else
                    {
                        //Quiere saber que cartas tengo
                        string mensaje = "5/" + nombre.Text;
                        // Enviamos al servidor el nombre tecleado
                        byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                        server.Send(msg);


                    }
                }
                private void desconectar_Click(object sender, EventArgs e)
                {
                    //Mensaje de desconexion
                    string mensaje = "0/";

                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);

                    //Nos deconectamos
                    conectado = false;
                    this.Invalidate(new Rectangle(20,20,40,40)); //Redibujar el formulario para actualizar el circulo
                    this.Update();
                    atender.Abort();

                    server.Shutdown(SocketShutdown.Both);
                    server.Close();
                }

                private void login_Click(object sender, EventArgs e)
                {
                    //Quiere iniciar session
                    string mensaje = "1/" + nombre.Text + "/" + Password.Text;
                    // Enviamos al servidor el nombre tecleado y la contraseña
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);


                }
                private void registrarse_Click(object sender, EventArgs e)
                {
                    //Quiere registrarse
                    string mensaje = "2/" + nombre.Text + "/" + Password.Text;
                    // Enviamos al servidor el nombre tecleado y la contraseña
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);

        
                }
                private void button1_Click(object sender, EventArgs e)
                {
                    //Quiere ver la lista de conectados
                    string mensaje = "6/";
                    // Enviamos al servidor el nombre tecleado
                    byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                    server.Send(msg);

                }
                private void label4_Click(object sender, EventArgs e)
                {
                }
        }
}

    namespace WindowsFormsApplication1
    {
        static class Program
        {
            // Este es el punto de entrada principal para la aplicación.
            [STAThread]
            static void Main()
            {
                Application.EnableVisualStyles();
                Application.SetCompatibleTextRenderingDefault(false);
                Application.Run(new Form1());
            }
        }
    }



