﻿using System;

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
            this.nombre = new System.Windows.Forms.TextBox();
            this.button2 = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.registrarse = new System.Windows.Forms.Button();
            this.login = new System.Windows.Forms.Button();
            this.Cartas = new System.Windows.Forms.RadioButton();
            this.Victorias = new System.Windows.Forms.RadioButton();
            this.label1 = new System.Windows.Forms.Label();
            this.Password = new System.Windows.Forms.TextBox();
            this.Dinero = new System.Windows.Forms.RadioButton();
            this.conectar = new System.Windows.Forms.Button();
            this.desconectar = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.ListaConectados = new System.Windows.Forms.Label();
            this.InvitarButton = new System.Windows.Forms.Button();
            this.InvitarBox = new System.Windows.Forms.TextBox();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Segoe UI", 16F, System.Drawing.FontStyle.Bold);
            this.label2.ForeColor = System.Drawing.Color.White;
            this.label2.Location = new System.Drawing.Point(35, 39);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(144, 45);
            this.label2.TabIndex = 1;
            this.label2.Text = "Nombre";
            // 
            // nombre
            // 
            this.nombre.Font = new System.Drawing.Font("Segoe UI", 12F);
            this.nombre.Location = new System.Drawing.Point(200, 50);
            this.nombre.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.nombre.Name = "nombre";
            this.nombre.Size = new System.Drawing.Size(244, 39);
            this.nombre.TabIndex = 3;
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.Color.ForestGreen;
            this.button2.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.button2.ForeColor = System.Drawing.Color.White;
            this.button2.Location = new System.Drawing.Point(213, 389);
            this.button2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(165, 35);
            this.button2.TabIndex = 5;
            this.button2.Text = "Enviar";
            this.button2.UseVisualStyleBackColor = false;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.LightSlateGray;
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
            this.groupBox1.Controls.Add(this.nombre);
            this.groupBox1.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.groupBox1.Location = new System.Drawing.Point(18, 175);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox1.Size = new System.Drawing.Size(840, 434);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Petición";
            // 
            // registrarse
            // 
            this.registrarse.BackColor = System.Drawing.Color.DimGray;
            this.registrarse.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.registrarse.ForeColor = System.Drawing.Color.White;
            this.registrarse.Location = new System.Drawing.Point(223, 169);
            this.registrarse.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.registrarse.Name = "registrarse";
            this.registrarse.Size = new System.Drawing.Size(155, 35);
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
            this.login.Location = new System.Drawing.Point(42, 169);
            this.login.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.login.Name = "login";
            this.login.Size = new System.Drawing.Size(155, 35);
            this.login.TabIndex = 13;
            this.login.Text = "Iniciar Sesión";
            this.login.UseVisualStyleBackColor = false;
            this.login.Click += new System.EventHandler(this.login_Click);
            // 
            // Cartas
            // 
            this.Cartas.AutoSize = true;
            this.Cartas.ForeColor = System.Drawing.Color.White;
            this.Cartas.Location = new System.Drawing.Point(174, 318);
            this.Cartas.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Cartas.Name = "Cartas";
            this.Cartas.Size = new System.Drawing.Size(200, 32);
            this.Cartas.TabIndex = 12;
            this.Cartas.TabStop = true;
            this.Cartas.Text = "Qué cartas tengo";
            this.Cartas.UseVisualStyleBackColor = true;
            // 
            // Victorias
            // 
            this.Victorias.AutoSize = true;
            this.Victorias.ForeColor = System.Drawing.Color.White;
            this.Victorias.Location = new System.Drawing.Point(174, 282);
            this.Victorias.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Victorias.Name = "Victorias";
            this.Victorias.Size = new System.Drawing.Size(305, 32);
            this.Victorias.TabIndex = 11;
            this.Victorias.TabStop = true;
            this.Victorias.Text = "Dime cuántas victorias llevo";
            this.Victorias.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 16F, System.Drawing.FontStyle.Bold);
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(35, 85);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(163, 45);
            this.label1.TabIndex = 10;
            this.label1.Text = "Password";
            // 
            // Password
            // 
            this.Password.Font = new System.Drawing.Font("Segoe UI", 12F);
            this.Password.Location = new System.Drawing.Point(200, 98);
            this.Password.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Password.Name = "Password";
            this.Password.PasswordChar = '*';
            this.Password.Size = new System.Drawing.Size(244, 39);
            this.Password.TabIndex = 9;
            // 
            // Dinero
            // 
            this.Dinero.AutoSize = true;
            this.Dinero.ForeColor = System.Drawing.Color.White;
            this.Dinero.Location = new System.Drawing.Point(174, 246);
            this.Dinero.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Dinero.Name = "Dinero";
            this.Dinero.Size = new System.Drawing.Size(232, 32);
            this.Dinero.TabIndex = 10;
            this.Dinero.TabStop = true;
            this.Dinero.Text = "Cuánto dinero tengo";
            this.Dinero.UseVisualStyleBackColor = true;
            // 
            // conectar
            // 
            this.conectar.BackColor = System.Drawing.Color.ForestGreen;
            this.conectar.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.conectar.ForeColor = System.Drawing.Color.White;
            this.conectar.Location = new System.Drawing.Point(18, 619);
            this.conectar.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.conectar.Name = "conectar";
            this.conectar.Size = new System.Drawing.Size(192, 58);
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
            this.desconectar.Location = new System.Drawing.Point(231, 619);
            this.desconectar.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.desconectar.Name = "desconectar";
            this.desconectar.Size = new System.Drawing.Size(192, 58);
            this.desconectar.TabIndex = 8;
            this.desconectar.Text = "Desconectar";
            this.desconectar.UseVisualStyleBackColor = false;
            this.desconectar.Click += new System.EventHandler(this.desconectar_Click);
            // 
            // label3
            // 
            this.label3.BackColor = System.Drawing.Color.Black;
            this.label3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label3.Font = new System.Drawing.Font("Segoe UI Variable Display", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.SystemColors.Control;
            this.label3.Location = new System.Drawing.Point(1044, 619);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(153, 37);
            this.label3.TabIndex = 9;
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label4
            // 
            this.label4.BackColor = System.Drawing.Color.Black;
            this.label4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label4.Font = new System.Drawing.Font("Segoe UI Variable Display", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.ForeColor = System.Drawing.SystemColors.Control;
            this.label4.Location = new System.Drawing.Point(1074, 656);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(96, 46);
            this.label4.TabIndex = 10;
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            this.label4.Click += new System.EventHandler(this.label4_Click);
            // 
            // ListaConectados
            // 
            this.ListaConectados.BackColor = System.Drawing.Color.White;
            this.ListaConectados.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.ListaConectados.Font = new System.Drawing.Font("Segoe UI Variable Display", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ListaConectados.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.ListaConectados.Location = new System.Drawing.Point(18, 681);
            this.ListaConectados.Name = "ListaConectados";
            this.ListaConectados.Size = new System.Drawing.Size(405, 61);
            this.ListaConectados.TabIndex = 11;
            this.ListaConectados.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // InvitarButton
            // 
            this.InvitarButton.BackColor = System.Drawing.Color.ForestGreen;
            this.InvitarButton.Font = new System.Drawing.Font("Segoe UI", 10F, System.Drawing.FontStyle.Bold);
            this.InvitarButton.ForeColor = System.Drawing.Color.White;
            this.InvitarButton.Location = new System.Drawing.Point(601, 169);
            this.InvitarButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.InvitarButton.Name = "InvitarButton";
            this.InvitarButton.Size = new System.Drawing.Size(165, 35);
            this.InvitarButton.TabIndex = 12;
            this.InvitarButton.Text = "Invitar";
            this.InvitarButton.UseVisualStyleBackColor = false;
            this.InvitarButton.Click += new System.EventHandler(this.InvitarButton_Click);
            // 
            // InvitarBox
            // 
            this.InvitarBox.Font = new System.Drawing.Font("Segoe UI", 12F);
            this.InvitarBox.Location = new System.Drawing.Point(567, 98);
            this.InvitarBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.InvitarBox.Name = "InvitarBox";
            this.InvitarBox.Size = new System.Drawing.Size(244, 39);
            this.InvitarBox.TabIndex = 15;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(64)))), ((int)(((byte)(0)))));
            this.ClientSize = new System.Drawing.Size(1779, 968);
            this.Controls.Add(this.ListaConectados);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.conectar);
            this.Controls.Add(this.desconectar);
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "Form1";
            this.Text = "Poker Game Client";
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.Form1_Paint);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox nombre;
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
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label ListaConectados;
        private System.Windows.Forms.Button InvitarButton;
        private System.Windows.Forms.TextBox InvitarBox;
    }
}
