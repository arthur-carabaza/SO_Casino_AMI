using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form3 : Form
    {
        Socket server;
        public Form3()
        {
            InitializeComponent();
        }
        string Gnombre;
        string Gcontraseña;
        public string GetNombre()
        {
            return Gnombre;
        }
        public string GetContraseña()
        {
            return Gcontraseña;
        }

        public void button1_Click(object sender, EventArgs e)
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

            else
            {
                MessageBox.Show("Inicio de sesión correcto");
                  string Gnombre = nombre.Text;
                 string Gcontraseña = contraseña.Text;
               
                
                    
                this.Close();

            }



        }
    }
}
