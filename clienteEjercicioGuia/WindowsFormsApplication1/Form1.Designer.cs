using System;

namespace WindowsFormsApplication1
{
    partial class Form1
    {
        /// <summary>
        /// Variable del diseñador requerida.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén utilizando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben eliminar; false en caso contrario, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido del método con el editor de código.
        /// </summary>
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
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(31, 31);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(110, 31);
            this.label2.TabIndex = 1;
            this.label2.Text = "Nombre";
            // 
            // nombre
            // 
            this.nombre.Location = new System.Drawing.Point(178, 40);
            this.nombre.Margin = new System.Windows.Forms.Padding(4);
            this.nombre.Name = "nombre";
            this.nombre.Size = new System.Drawing.Size(217, 22);
            this.nombre.TabIndex = 3;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(178, 311);
            this.button2.Margin = new System.Windows.Forms.Padding(4);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(100, 28);
            this.button2.TabIndex = 5;
            this.button2.Text = "Enviar";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.SystemColors.ActiveBorder;
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
            this.groupBox1.Location = new System.Drawing.Point(16, 140);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox1.Size = new System.Drawing.Size(484, 347);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Peticion";
            // 
            // registrarse
            // 
            this.registrarse.Location = new System.Drawing.Point(198, 135);
            this.registrarse.Margin = new System.Windows.Forms.Padding(4);
            this.registrarse.Name = "registrarse";
            this.registrarse.Size = new System.Drawing.Size(138, 28);
            this.registrarse.TabIndex = 14;
            this.registrarse.Text = "Registrarse";
            this.registrarse.UseVisualStyleBackColor = true;
            this.registrarse.Click += new System.EventHandler(this.registrarse_Click);
            // 
            // login
            // 
            this.login.Location = new System.Drawing.Point(37, 135);
            this.login.Margin = new System.Windows.Forms.Padding(4);
            this.login.Name = "login";
            this.login.Size = new System.Drawing.Size(138, 28);
            this.login.TabIndex = 13;
            this.login.Text = "Iniciar Session";
            this.login.UseVisualStyleBackColor = true;
            this.login.Click += new System.EventHandler(this.login_Click);
            // 
            // Cartas
            // 
            this.Cartas.AutoSize = true;
            this.Cartas.Location = new System.Drawing.Point(155, 254);
            this.Cartas.Margin = new System.Windows.Forms.Padding(4);
            this.Cartas.Name = "Cartas";
            this.Cartas.Size = new System.Drawing.Size(130, 20);
            this.Cartas.TabIndex = 12;
            this.Cartas.TabStop = true;
            this.Cartas.Text = "Que cartas tengo";
            this.Cartas.UseVisualStyleBackColor = true;
            // 
            // Victorias
            // 
            this.Victorias.AutoSize = true;
            this.Victorias.Location = new System.Drawing.Point(155, 226);
            this.Victorias.Margin = new System.Windows.Forms.Padding(4);
            this.Victorias.Name = "Victorias";
            this.Victorias.Size = new System.Drawing.Size(195, 20);
            this.Victorias.TabIndex = 11;
            this.Victorias.TabStop = true;
            this.Victorias.Text = "Dime cuantas victorias llevo";
            this.Victorias.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(31, 68);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(134, 31);
            this.label1.TabIndex = 10;
            this.label1.Text = "Password";
            // 
            // Password
            // 
            this.Password.Location = new System.Drawing.Point(178, 77);
            this.Password.Margin = new System.Windows.Forms.Padding(4);
            this.Password.Name = "Password";
            this.Password.Size = new System.Drawing.Size(217, 22);
            this.Password.TabIndex = 9;
            // 
            // Dinero
            // 
            this.Dinero.AutoSize = true;
            this.Dinero.Location = new System.Drawing.Point(155, 198);
            this.Dinero.Margin = new System.Windows.Forms.Padding(4);
            this.Dinero.Name = "Dinero";
            this.Dinero.Size = new System.Drawing.Size(181, 20);
            this.Dinero.TabIndex = 8;
            this.Dinero.TabStop = true;
            this.Dinero.Text = "Dime cuanto dinero tengo";
            this.Dinero.UseVisualStyleBackColor = true;
            // 
            // conectar
            // 
            this.conectar.Location = new System.Drawing.Point(16, 85);
            this.conectar.Margin = new System.Windows.Forms.Padding(4);
            this.conectar.Name = "conectar";
            this.conectar.Size = new System.Drawing.Size(175, 47);
            this.conectar.TabIndex = 7;
            this.conectar.Text = "Conectar";
            this.conectar.UseVisualStyleBackColor = true;
            this.conectar.Click += new System.EventHandler(this.conectar_Click);
            // 
            // desconectar
            // 
            this.desconectar.Location = new System.Drawing.Point(325, 85);
            this.desconectar.Margin = new System.Windows.Forms.Padding(4);
            this.desconectar.Name = "desconectar";
            this.desconectar.Size = new System.Drawing.Size(175, 47);
            this.desconectar.TabIndex = 8;
            this.desconectar.Text = "Desconectar";
            this.desconectar.UseVisualStyleBackColor = true;
            this.desconectar.Click += new System.EventHandler(this.desconectar_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(988, 692);
            this.Controls.Add(this.desconectar);
            this.Controls.Add(this.conectar);
            this.Controls.Add(this.groupBox1);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox nombre;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton Dinero;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox Password;
        private System.Windows.Forms.Button conectar;
        private System.Windows.Forms.Button desconectar;
        private System.Windows.Forms.RadioButton Victorias;
        private System.Windows.Forms.RadioButton Cartas;
        private System.Windows.Forms.Button registrarse;
        private System.Windows.Forms.Button login;
    }
}

