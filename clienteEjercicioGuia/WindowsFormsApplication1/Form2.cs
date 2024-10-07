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
    
    public partial class Form2 : Form
    {
        Socket server;
        public Form2()
        {
            InitializeComponent();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void conectar_Click(object sender, EventArgs e)
        {
            // Quiere saber la longitud
            string mensaje = "1/" + nombre.Text + "/" + contraseña.Text;
            // Enviamos al servidor el nombre tecleado
            byte[] msg = System.Text.Encoding.ASCII.GetBytes(mensaje);
            server.Send(msg);

            //Recibimos la respuesta del servidor
            byte[] msg2 = new byte[80];
            server.Receive(msg2);
            mensaje = Encoding.ASCII.GetString(msg2).Split('\0')[0];
            int mensaje1 = Convert.ToInt32(mensaje, 0);

            if (mensaje1 != 0)
            {
                MessageBox.Show("Error");
            }

            else { 
                MessageBox.Show("Registro Correcto");

               this.Close();

            }

        }

        private void textBox1_TextChanged_1(object sender, EventArgs e)
        {

        }
    }
}
