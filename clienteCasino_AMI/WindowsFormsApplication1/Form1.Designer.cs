using System;

namespace WindowsFormsApplication1
{
    partial class Form1
    {
        private System.ComponentModel.IContainer components = null;

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        private void InitializeComponent()
        {
            this.label2 = new System.Windows.Forms.Label();
            this.nombreTextBox = new System.Windows.Forms.TextBox();
            this.button2 = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.query = new System.Windows.Forms.TextBox();
            this.dardebaja = new System.Windows.Forms.Button();
            this.botonInciarSala = new System.Windows.Forms.Button();
            this.labelInvitado = new System.Windows.Forms.Label();
            this.InvitarButton = new System.Windows.Forms.Button();
            this.InvitarBox = new System.Windows.Forms.TextBox();
            this.registrarse = new System.Windows.Forms.Button();
            this.login = new System.Windows.Forms.Button();
            this.Cartas = new System.Windows.Forms.RadioButton();
            this.Victorias = new System.Windows.Forms.RadioButton();
            this.label1 = new System.Windows.Forms.Label();
            this.Password = new System.Windows.Forms.TextBox();
            this.Dinero = new System.Windows.Forms.RadioButton();
            this.conectar = new System.Windows.Forms.Button();
            this.desconectar = new System.Windows.Forms.Button();
            this.NombrePartida = new System.Windows.Forms.Label();
            this.ListaConectados = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Segoe UI", 16F, System.Drawing.FontStyle.Bold);
            this.label2.ForeColor = System.Drawing.Color.White;
            this.label2.Location = new System.Drawing.Point(31, 31);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(123, 37);
            this.label2.TabIndex = 1;
            this.label2.Text = "Nombre";
            // 
            // nombreTextBox
            // 
            this.nombreTextBox.Font = new System.Drawing.Font("Segoe UI", 12F);
            this.nombreTextBox.Location = new System.Drawing.Point(178, 40);
            this.nombreTextBox.Margin = new System.Windows.Forms.Padding(4);
            this.nombreTextBox.Name = "nombreTextBox";
            this.nombreTextBox.Size = new System.Drawing.Size(217, 34);
            this.nombreTextBox.TabIndex = 3;
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.Color.ForestGreen;
            this.button2.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.button2.ForeColor = System.Drawing.Color.White;
            this.button2.Location = new System.Drawing.Point(292, 305);
            this.button2.Margin = new System.Windows.Forms.Padding(4);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(147, 34);
            this.button2.TabIndex = 5;
            this.button2.Text = "Enviar";
            this.button2.UseVisualStyleBackColor = false;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.LightSlateGray;
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.query);
            this.groupBox1.Controls.Add(this.dardebaja);
            this.groupBox1.Controls.Add(this.botonInciarSala);
            this.groupBox1.Controls.Add(this.labelInvitado);
            this.groupBox1.Controls.Add(this.InvitarButton);
            this.groupBox1.Controls.Add(this.InvitarBox);
            this.groupBox1.Controls.Add(this.registrarse);
            this.groupBox1.Controls.Add(this.login);
            this.groupBox1.Controls.Add(this.Cartas);
            this.groupBox1.Controls.Add(this.Victorias);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.Password);
            this.groupBox1.Controls.Add(this.Dinero);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.button2);
            this.groupBox1.Controls.Add(this.nombreTextBox);
            this.groupBox1.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.groupBox1.Location = new System.Drawing.Point(16, 140);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox1.Size = new System.Drawing.Size(932, 347);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "SO 2024-2025";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Segoe UI", 16F, System.Drawing.FontStyle.Bold);
            this.label3.ForeColor = System.Drawing.Color.White;
            this.label3.Location = new System.Drawing.Point(481, 27);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(407, 37);
            this.label3.TabIndex = 20;
            this.label3.Text = "Invita a alguien para empezar!";
            // 
            // query
            // 
            this.query.Font = new System.Drawing.Font("Segoe UI", 12F);
            this.query.Location = new System.Drawing.Point(62, 305);
            this.query.Margin = new System.Windows.Forms.Padding(4);
            this.query.Name = "query";
            this.query.Size = new System.Drawing.Size(217, 34);
            this.query.TabIndex = 19;
            // 
            // dardebaja
            // 
            this.dardebaja.BackColor = System.Drawing.Color.DimGray;
            this.dardebaja.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.dardebaja.ForeColor = System.Drawing.Color.White;
            this.dardebaja.Location = new System.Drawing.Point(330, 135);
            this.dardebaja.Margin = new System.Windows.Forms.Padding(4);
            this.dardebaja.Name = "dardebaja";
            this.dardebaja.Size = new System.Drawing.Size(154, 41);
            this.dardebaja.TabIndex = 18;
            this.dardebaja.Text = "Darse de Baja";
            this.dardebaja.UseVisualStyleBackColor = false;
            this.dardebaja.Click += new System.EventHandler(this.dardebaja_Click);
            // 
            // botonInciarSala
            // 
            this.botonInciarSala.BackColor = System.Drawing.Color.Firebrick;
            this.botonInciarSala.Enabled = false;
            this.botonInciarSala.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.botonInciarSala.ForeColor = System.Drawing.Color.White;
            this.botonInciarSala.Location = new System.Drawing.Point(617, 253);
            this.botonInciarSala.Margin = new System.Windows.Forms.Padding(4);
            this.botonInciarSala.Name = "botonInciarSala";
            this.botonInciarSala.Size = new System.Drawing.Size(147, 28);
            this.botonInciarSala.TabIndex = 17;
            this.botonInciarSala.Text = "Iniciar Sala";
            this.botonInciarSala.UseVisualStyleBackColor = false;
            this.botonInciarSala.Click += new System.EventHandler(this.botonInciarSala_Click);
            // 
            // labelInvitado
            // 
            this.labelInvitado.BackColor = System.Drawing.Color.White;
            this.labelInvitado.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.labelInvitado.Font = new System.Drawing.Font("Segoe UI Variable Display", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.labelInvitado.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.labelInvitado.Location = new System.Drawing.Point(546, 188);
            this.labelInvitado.Name = "labelInvitado";
            this.labelInvitado.Size = new System.Drawing.Size(299, 40);
            this.labelInvitado.TabIndex = 16;
            this.labelInvitado.Text = "Invitado: Ninguno";
            this.labelInvitado.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // InvitarButton
            // 
            this.InvitarButton.BackColor = System.Drawing.Color.ForestGreen;
            this.InvitarButton.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.InvitarButton.ForeColor = System.Drawing.Color.White;
            this.InvitarButton.Location = new System.Drawing.Point(617, 135);
            this.InvitarButton.Margin = new System.Windows.Forms.Padding(4);
            this.InvitarButton.Name = "InvitarButton";
            this.InvitarButton.Size = new System.Drawing.Size(147, 28);
            this.InvitarButton.TabIndex = 12;
            this.InvitarButton.Text = "Invitar";
            this.InvitarButton.UseVisualStyleBackColor = false;
            this.InvitarButton.Click += new System.EventHandler(this.InvitarButton_Click);
            // 
            // InvitarBox
            // 
            this.InvitarBox.Font = new System.Drawing.Font("Segoe UI", 12F);
            this.InvitarBox.Location = new System.Drawing.Point(576, 78);
            this.InvitarBox.Margin = new System.Windows.Forms.Padding(4);
            this.InvitarBox.Name = "InvitarBox";
            this.InvitarBox.Size = new System.Drawing.Size(217, 34);
            this.InvitarBox.TabIndex = 15;
            // 
            // registrarse
            // 
            this.registrarse.BackColor = System.Drawing.Color.DimGray;
            this.registrarse.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.registrarse.ForeColor = System.Drawing.Color.White;
            this.registrarse.Location = new System.Drawing.Point(171, 135);
            this.registrarse.Margin = new System.Windows.Forms.Padding(4);
            this.registrarse.Name = "registrarse";
            this.registrarse.Size = new System.Drawing.Size(151, 41);
            this.registrarse.TabIndex = 14;
            this.registrarse.Text = "Registrarse";
            this.registrarse.UseVisualStyleBackColor = false;
            this.registrarse.Click += new System.EventHandler(this.registrarse_Click);
            // 
            // login
            // 
            this.login.BackColor = System.Drawing.Color.DimGray;
            this.login.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.login.ForeColor = System.Drawing.Color.White;
            this.login.Location = new System.Drawing.Point(8, 135);
            this.login.Margin = new System.Windows.Forms.Padding(4);
            this.login.Name = "login";
            this.login.Size = new System.Drawing.Size(155, 41);
            this.login.TabIndex = 13;
            this.login.Text = "Iniciar Sesión";
            this.login.UseVisualStyleBackColor = false;
            this.login.Click += new System.EventHandler(this.login_Click);
            // 
            // Cartas
            // 
            this.Cartas.AutoSize = true;
            this.Cartas.ForeColor = System.Drawing.Color.White;
            this.Cartas.Location = new System.Drawing.Point(155, 254);
            this.Cartas.Margin = new System.Windows.Forms.Padding(4);
            this.Cartas.Name = "Cartas";
            this.Cartas.Size = new System.Drawing.Size(355, 27);
            this.Cartas.TabIndex = 12;
            this.Cartas.TabStop = true;
            this.Cartas.Text = "Que salas se han creado en este tiempo ?";
            this.Cartas.UseVisualStyleBackColor = true;
            // 
            // Victorias
            // 
            this.Victorias.AutoSize = true;
            this.Victorias.ForeColor = System.Drawing.Color.White;
            this.Victorias.Location = new System.Drawing.Point(155, 226);
            this.Victorias.Margin = new System.Windows.Forms.Padding(4);
            this.Victorias.Name = "Victorias";
            this.Victorias.Size = new System.Drawing.Size(264, 27);
            this.Victorias.TabIndex = 11;
            this.Victorias.TabStop = true;
            this.Victorias.Text = "Cuantos mensajes he enviado";
            this.Victorias.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 16F, System.Drawing.FontStyle.Bold);
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(31, 68);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(139, 37);
            this.label1.TabIndex = 10;
            this.label1.Text = "Password";
            // 
            // Password
            // 
            this.Password.Font = new System.Drawing.Font("Segoe UI", 12F);
            this.Password.Location = new System.Drawing.Point(178, 78);
            this.Password.Margin = new System.Windows.Forms.Padding(4);
            this.Password.Name = "Password";
            this.Password.PasswordChar = '*';
            this.Password.Size = new System.Drawing.Size(217, 34);
            this.Password.TabIndex = 9;
            // 
            // Dinero
            // 
            this.Dinero.AutoSize = true;
            this.Dinero.ForeColor = System.Drawing.Color.White;
            this.Dinero.Location = new System.Drawing.Point(155, 197);
            this.Dinero.Margin = new System.Windows.Forms.Padding(4);
            this.Dinero.Name = "Dinero";
            this.Dinero.Size = new System.Drawing.Size(265, 27);
            this.Dinero.TabIndex = 10;
            this.Dinero.TabStop = true;
            this.Dinero.Text = "Con quien he estado en sala ?";
            this.Dinero.UseVisualStyleBackColor = true;
            // 
            // conectar
            // 
            this.conectar.BackColor = System.Drawing.Color.ForestGreen;
            this.conectar.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.conectar.ForeColor = System.Drawing.Color.White;
            this.conectar.Location = new System.Drawing.Point(16, 495);
            this.conectar.Margin = new System.Windows.Forms.Padding(4);
            this.conectar.Name = "conectar";
            this.conectar.Size = new System.Drawing.Size(171, 46);
            this.conectar.TabIndex = 7;
            this.conectar.Text = "Conectar";
            this.conectar.UseVisualStyleBackColor = false;
            this.conectar.Click += new System.EventHandler(this.conectar_Click);
            // 
            // desconectar
            // 
            this.desconectar.BackColor = System.Drawing.Color.Firebrick;
            this.desconectar.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.desconectar.ForeColor = System.Drawing.Color.White;
            this.desconectar.Location = new System.Drawing.Point(205, 495);
            this.desconectar.Margin = new System.Windows.Forms.Padding(4);
            this.desconectar.Name = "desconectar";
            this.desconectar.Size = new System.Drawing.Size(171, 46);
            this.desconectar.TabIndex = 8;
            this.desconectar.Text = "Desconectar";
            this.desconectar.UseVisualStyleBackColor = false;
            this.desconectar.Click += new System.EventHandler(this.desconectar_Click);
            // 
            // NombrePartida
            // 
            this.NombrePartida.BackColor = System.Drawing.Color.Black;
            this.NombrePartida.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.NombrePartida.Font = new System.Drawing.Font("Segoe UI Variable Display", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.NombrePartida.ForeColor = System.Drawing.SystemColors.Control;
            this.NombrePartida.Location = new System.Drawing.Point(78, 19);
            this.NombrePartida.Name = "NombrePartida";
            this.NombrePartida.Size = new System.Drawing.Size(136, 30);
            this.NombrePartida.TabIndex = 9;
            this.NombrePartida.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // ListaConectados
            // 
            this.ListaConectados.BackColor = System.Drawing.Color.White;
            this.ListaConectados.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.ListaConectados.Font = new System.Drawing.Font("Segoe UI Variable Display", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ListaConectados.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.ListaConectados.Location = new System.Drawing.Point(16, 545);
            this.ListaConectados.Name = "ListaConectados";
            this.ListaConectados.Size = new System.Drawing.Size(360, 49);
            this.ListaConectados.TabIndex = 11;
            this.ListaConectados.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(64)))), ((int)(((byte)(0)))));
            this.ClientSize = new System.Drawing.Size(1089, 616);
            this.Controls.Add(this.ListaConectados);
            this.Controls.Add(this.NombrePartida);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.conectar);
            this.Controls.Add(this.desconectar);
            this.Name = "Form1";
            this.Text = "Poker Game Client";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.Form1_Paint);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox nombreTextBox;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton Cartas;
        private System.Windows.Forms.RadioButton Victorias;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox Password;
        private System.Windows.Forms.RadioButton Dinero;
        private System.Windows.Forms.Button conectar;
        private System.Windows.Forms.Button desconectar;
        private System.Windows.Forms.Button registrarse;
        private System.Windows.Forms.Button login;
        private System.Windows.Forms.Label NombrePartida;
        private System.Windows.Forms.Label ListaConectados;
        private System.Windows.Forms.Button InvitarButton;
        private System.Windows.Forms.TextBox InvitarBox;
        private System.Windows.Forms.Button botonInciarSala;
        private System.Windows.Forms.Label labelInvitado;
        private System.Windows.Forms.Button dardebaja;
        private System.Windows.Forms.TextBox query;
        private System.Windows.Forms.Label label3;
    }
}
