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

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        Socket server;
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
           
        }
        string nombre;
        string contraseña;


        private void conectar_Click(object sender, EventArgs e)
        {
            //Creamos un IPEndPoint con el ip del servidor y puerto del servidor 
            //al que deseamos conectarnos
            IPAddress direc = IPAddress.Parse("192.168.56.101");
            IPEndPoint ipep = new IPEndPoint(direc, 9050);


            //Creamos el socket 
            server = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            try
            {
                server.Connect(ipep);//Intentamos conectar el socket
                this.BackColor = Color.Green;
                MessageBox.Show("Conectado");
            }

            catch (SocketException )
            {
                //Si hay excepcion imprimimos error y salimos del programa con return 
                MessageBox.Show("No he podido conectar con el servidor");
                return;
            }
        }


        public void button2_Click(object sender, EventArgs e)
        {
            // Asumiendo que 'nombre' es una variable definida anteriormente
            // Asumiendo que 'nombre' es una variable definida anteriormente
            string mensaje1;

            // Verifica si el control 'Ganadas' está seleccionado
            if (Dinero.Checked)
            {
                // Crear el mensaje a enviar
                mensaje1 = "3/" + nombre;

                // Convertir el mensaje a bytes y enviarlo al servidor
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje1);
                server.Send(msg);

                // Recibir la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);

                // Convertir la respuesta a string y eliminar caracteres nulos
                mensaje1 = Encoding.ASCII.GetString(msg2).Split('\0')[0];

                // Convertir la respuesta a un entero
                int mensaje71 = Convert.ToInt32(mensaje1);

                // Verificar la respuesta
                if (mensaje71 != 0)
                {
                    MessageBox.Show("Error");
                }
                else
                {
                    MessageBox.Show("El usuario tiene: " + mensaje1);
                    
                }


            }
            
            if (Ganadas.Checked)
            {
                // Crear el mensaje a enviar
                mensaje1 = "4/" + nombre;

                // Convertir el mensaje a bytes y enviarlo al servidor
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje1);
                server.Send(msg);

                // Recibir la respuesta del servidor
                byte[] msg2 = new byte[80];
                server.Receive(msg2);

                // Convertir la respuesta a string y eliminar caracteres nulos
                mensaje1 = Encoding.ASCII.GetString(msg2).Split('\0')[0];

                // Convertir la respuesta a un entero
                int mensaje71 = Convert.ToInt32(mensaje1);

                // Verificar la respuesta
                if (mensaje71 != 0)
                {
                    MessageBox.Show("Error");
                }
                else
                {
                    MessageBox.Show("El usuario tiene: " + mensaje1);
                    
                }


            }






        }

        private void desconectar_Click(object sender, EventArgs e)
        {
            //Mensaje de desconexion
            string mensaje = "0/";

            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);
            
            //Nos deconectamos
            this.BackColor = Color.Gray;
            server.Shutdown(SocketShutdown.Both);
            server.Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Form2 form2 = new Form2();
            form2.Show();
        }

        public void button1_Click(object sender, EventArgs e)
        {
            
            Form3 form3 = new Form3();
            form3.Show();
            string Nombre = form3.GetNombre();
            
            
        }

        private void Dinero_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void Ganadas_CheckedChanged(object sender, EventArgs e)
        {

        }
    }

 }
 
