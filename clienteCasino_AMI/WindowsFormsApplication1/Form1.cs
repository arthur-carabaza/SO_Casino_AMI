﻿using System;
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
        Thread atender;

        bool conectado = false;

        delegate void DelegadoParaEscribir(string mensaje);
        delegate void DelegadoParaActualizarLista(string mensaje);
        delegate void DelegadoParaMostrarMensaje(string mensaje);
        delegate void DelegadoParaActualizarNombrePartida(string nombre);

        private void ActualizarNombrePartida(string nombre)
        {
            NombrePartida.Text = nombre;
        }


        private void EscribirEnChatbox(string mensaje)
        {
            Chatbox.AppendText(mensaje + Environment.NewLine);
        }

        private void ActualizarListaConectados(string mensaje)
        {
            ListaConectados.Text = mensaje;
        }

        private void MostrarMensaje(string mensaje)
        {
            MessageBox.Show(mensaje);
        }


        public Form1()
        {
            InitializeComponent();
                
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
                //Recibimos mensaje del servidor
                byte[] msg2 = new byte[1024]; //Memoria ampliada de 1024 bytes
                int bytesRecibidos = server.Receive(msg2); 
                string mensajeCompleto = Encoding.ASCII.GetString(msg2, 0, bytesRecibidos); 
                string[] trozos = mensajeCompleto.Split('/');
                int codigo = Convert.ToInt32(trozos[0]); 
                string mensaje = trozos.Length > 1 ? trozos[1].Split('\0')[0] : string.Empty; 
                string nombre = nombreTextBox.Text;


                switch (codigo)
                {
                    case 1: //Respuesta a iniciar sesión
                        this.Invoke(new DelegadoParaMostrarMensaje(MostrarMensaje), new object[] { mensaje });
                        this.Invoke(new DelegadoParaActualizarNombrePartida(ActualizarNombrePartida), new object[] { nombre });
                    break;


                    case 2: //Respuesta a registro
                        MessageBox.Show(mensaje);
                        break;

                    case 3: //respuesta a query de cuanto dinero
                        MessageBox.Show(mensaje);
                        break;

                    case 4: //respuesta a query cuantas visctoria 
                        MessageBox.Show(mensaje);
                        break;

                    case 5: //Respuesta a query cuantas victorias 
                        MessageBox.Show(mensaje);
                        break;

                    case 6: //Notificacion de conectados

                        this.Invoke(new DelegadoParaActualizarLista(ActualizarListaConectados), new object[] { mensaje }); 
                        break;

                    case 7: //Notificacion de invitacion

                        DialogResult RespuestaInv = MessageBox.Show(mensaje + "le han invitado a una partida.\n Quiere unirse?", "Respuesta invitacion", MessageBoxButtons.YesNo, MessageBoxIcon.Question);
                        if (RespuestaInv == DialogResult.Yes)
                        {
                            string mensg = "8/"+mensaje+"/SI";
                            // Enviamos al servidor la respuesta de la invitacion
                            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensg);
                            server.Send(msg);
                        }
                        else
                        {
                            string mensg = "8/" + mensaje + "/NO";
                            // Enviamos al servidor la respuesta de la invitacion
                            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensg);
                            server.Send(msg);
                        }
                        break;

                    case 8:
                        if(mensaje == "SI")
                        {
                            MessageBox.Show("Su invitación ha sido aceptada");
                        }
                        else
                        {
                            DialogResult result = MessageBox.Show("Su invitación ha sido rechazada, quiere iniciar igualmente la partida?","invitacion",MessageBoxButtons.YesNo,MessageBoxIcon.Question);
                            if (result == DialogResult.Yes)
                            {
                                MessageBox.Show("La partida se iniciará");
                            }
                            else
                            {
                                MessageBox.Show("La partida de cancela");
                            }

                        }
                        break;

                    case 9:  //Manejar mensajes de creacion de partidas en general 
                        this.Invoke(new DelegadoParaMostrarMensaje(MostrarMensaje), new object[] { mensaje }); 
                        break;

                    case 10: //Mensaje de chat
                        this.Invoke(new DelegadoParaEscribir(EscribirEnChatbox), new object[] { mensaje }); 
                        break;
                }
            }
        }

        private void conectar_Click(object sender, EventArgs e)
        {
            //Creamos un IPEndPoint con el ip del servidor y puerto del servidor 
            //al que deseamos conectarnos
            IPAddress direc = IPAddress.Parse("192.168.56.101");
            IPEndPoint ipep = new IPEndPoint(direc, 50000);


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

            //Poner en marcha el thread que atendera los mensajes del servidro
            ThreadStart ts = delegate { AtenderServidor(); };
            atender = new Thread(ts);
            atender.Start();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            
            if (Dinero.Checked)
            {
                //Quiere saber cuanto dinero tiene
                string mensaje = "3/" + nombreTextBox.Text;
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
                string mensaje = "4/" + nombreTextBox.Text;
                // Enviamos al servidor el nombre tecleado
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);
            }
            else
            {
                //Quiere saber que cartas tengo
                string mensaje = "5/" + nombreTextBox.Text;
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
            atender.Abort();
            this.Invalidate(new Rectangle(20,20,40,40)); //Redibujar el formulario para actualizar el circulo
            this.Update();

            ListaConectados.Text = null;
            NombrePartida.Text = null;
            nombreTextBox.Text = null;
            Password.Text = null;

            server.Shutdown(SocketShutdown.Both);
            server.Close();
        }

        private void login_Click(object sender, EventArgs e)
        {
            //Quiere iniciar session
            string mensaje = "1/" + nombreTextBox.Text + "/" + Password.Text;
            // Enviamos al servidor el nombre tecleado y la contraseña
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);          
        }
        private void registrarse_Click(object sender, EventArgs e)
        {
            //Quiere registrarse
            string mensaje = "2/" + nombreTextBox.Text + "/" + Password.Text;
            // Enviamos al servidor el nombre tecleado y la contraseña
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);
        }
        private void label4_Click(object sender, EventArgs e)
        {
        }

        private void InvitarButton_Click(object sender, EventArgs e)
        {
            if (InvitarBox.Text == null)
            {
                MessageBox.Show("Escriba un nombre de usuario que quiera invitar");
            }
            else
            {
                string NombreInvitado = InvitarBox.Text;
                string mensaje = "7/" + NombreInvitado;
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);
            }

            InvitarBox.Text = null;
        }

        private void EnviarMensaje_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrWhiteSpace(MensajeChat.Text)) { 
                MessageBox.Show("Escriba un mensaje antes de enviarlo");
            }
            else
            {
                string mensaje = "10/" + nombreTextBox.Text + "/" + MensajeChat.Text; 
                byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje); 
                server.Send(msg); 
                MensajeChat.Text = ""; // Limpiar el campo de texto después de enviar el mensaje
            }
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



