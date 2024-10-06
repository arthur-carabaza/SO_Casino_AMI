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
            this.button2 = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.Ganadas = new System.Windows.Forms.RadioButton();
            this.Dinero = new System.Windows.Forms.RadioButton();
            this.conectar = new System.Windows.Forms.Button();
            this.desconectar = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(134, 253);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 5;
            this.button2.Text = "Enviar";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.groupBox1.Controls.Add(this.Ganadas);
            this.groupBox1.Controls.Add(this.Dinero);
            this.groupBox1.Controls.Add(this.button2);
            this.groupBox1.Location = new System.Drawing.Point(12, 114);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(363, 282);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Peticion";
            // 
            // Ganadas
            // 
            this.Ganadas.AutoSize = true;
            this.Ganadas.Location = new System.Drawing.Point(116, 149);
            this.Ganadas.Name = "Ganadas";
            this.Ganadas.Size = new System.Drawing.Size(133, 17);
            this.Ganadas.TabIndex = 7;
            this.Ganadas.TabStop = true;
            this.Ganadas.Text = "Dime partidas ganadas";
            this.Ganadas.UseVisualStyleBackColor = true;
            this.Ganadas.CheckedChanged += new System.EventHandler(this.Ganadas_CheckedChanged);
            // 
            // Dinero
            // 
            this.Dinero.AutoSize = true;
            this.Dinero.Location = new System.Drawing.Point(116, 87);
            this.Dinero.Name = "Dinero";
            this.Dinero.Size = new System.Drawing.Size(94, 17);
            this.Dinero.TabIndex = 8;
            this.Dinero.TabStop = true;
            this.Dinero.Text = "Dime mi dinero";
            this.Dinero.UseVisualStyleBackColor = true;
            this.Dinero.CheckedChanged += new System.EventHandler(this.Dinero_CheckedChanged);
            // 
            // conectar
            // 
            this.conectar.Location = new System.Drawing.Point(12, 69);
            this.conectar.Name = "conectar";
            this.conectar.Size = new System.Drawing.Size(131, 38);
            this.conectar.TabIndex = 7;
            this.conectar.Text = "Conectar";
            this.conectar.UseVisualStyleBackColor = true;
            this.conectar.Click += new System.EventHandler(this.conectar_Click);
            // 
            // desconectar
            // 
            this.desconectar.Location = new System.Drawing.Point(244, 69);
            this.desconectar.Name = "desconectar";
            this.desconectar.Size = new System.Drawing.Size(131, 38);
            this.desconectar.TabIndex = 8;
            this.desconectar.Text = "Desconectar";
            this.desconectar.UseVisualStyleBackColor = true;
            this.desconectar.Click += new System.EventHandler(this.desconectar_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(244, 402);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(131, 38);
            this.button1.TabIndex = 9;
            this.button1.Text = "Iniciar Sesion";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(40, 402);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(131, 38);
            this.button3.TabIndex = 10;
            this.button3.Text = "Registrarse";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(741, 562);
            this.Controls.Add(this.button3);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.desconectar);
            this.Controls.Add(this.conectar);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton Ganadas;
        private System.Windows.Forms.RadioButton Dinero;
        private System.Windows.Forms.Button conectar;
        private System.Windows.Forms.Button desconectar;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button3;
    }
}

