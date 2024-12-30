﻿using System;
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
    public partial class FormChat : Form
    {
        Socket server;
        string username;
        int cont;
        public FormChat(Socket server, string username, int cont)
        {
            InitializeComponent();
            this.server = server;
            this.cont = cont;
            this.username = username;
        }

        

        private void txtMensaje_TextChanged(object sender, EventArgs e)
        {

        }

        public void EscribirMensaje(string mensaje)
        {
            txtChat.AppendText(mensaje+Environment.NewLine);
        }

        private void btnEnviar_Click(object sender, EventArgs e)
        {
            if (!string.IsNullOrWhiteSpace(txtMensaje.Text))
            {
                string mensaje = "10/" + cont + "/" + username + "/" + txtMensaje.Text;
                byte[] msg = Encoding.ASCII.GetBytes(mensaje);
                server.Send(msg);

                txtChat.AppendText("Yo: " + txtMensaje.Text + Environment.NewLine);
                txtMensaje.Text = "";
            }
            else
            {
                MessageBox.Show("Escriba un mensaje antes de enviarlo");
            }
        }

        private void FormChat_Load(object sender, EventArgs e)
        {
            txtnumForms.Text = cont.ToString();
        }
    }
}