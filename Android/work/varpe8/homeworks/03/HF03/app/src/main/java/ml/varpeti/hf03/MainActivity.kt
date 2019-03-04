package ml.varpeti.hf03

import android.content.Intent
import android.database.Cursor
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.provider.ContactsContract
import android.widget.Button
import android.widget.LinearLayout

@Suppress("NULLABILITY_MISMATCH_BASED_ON_JAVA_ANNOTATIONS")
class MainActivity : AppCompatActivity()
{

    override fun onCreate(savedInstanceState: Bundle?)
    {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Szerintem ez a legszebb, legegyszerübb út.
        Thread(Runnable(function = {loadContacts()}), "loadContactsAsync").start()
    }

    @Suppress("NAME_SHADOWING")
    fun loadContacts()
    {
        // Cursor az összes Contactra
        val cursor : Cursor = contentResolver.query(ContactsContract.Contacts.CONTENT_URI,null,null,null,null)!!
        // selection: "DISPLAY_NAME like 'Diófa'"

        //Ha valami elromlik is zárjuk le a cursort
        try
        {
            var ll01 = findViewById<LinearLayout>(R.id.ll01)

            //Az első elemtől járja be a cursort
            while (cursor.moveToNext())
            {
                //Adatok lekérése
                val id = cursor.getString(cursor.getColumnIndex(ContactsContract.Contacts._ID))
                val name = cursor.getString(cursor.getColumnIndex(ContactsContract.Contacts.DISPLAY_NAME))
                val lookUpKey = cursor.getString(cursor.getColumnIndex(ContactsContract.Contacts.LOOKUP_KEY))


                //Mivel nem lehet elérni innen Postol
                ll01.post(Runnable()
                {
                    // name nevű gombokat hoz létre, az ID meg fog egyezni az adatbázisbeli ID-vel.
                    var b = Button(this)
                    b.id=id.toInt()
                    b.text=name
                    b.setOnClickListener{
                        var id = it.id.toString()

                        val int = Intent(this, ShowContactActivity::class.java)
                        int.putExtra("id", id)
                        int.putExtra("lookUpKey",lookUpKey)
                        startActivityForResult(int,0)
                        // Kattintás esetén az ID-vel átmegy a ShowContactActivity-re.
                    }
                    ll01.addView(b)
                })
            }
        }
        finally
        {
            cursor.close()
        }
    }
}
