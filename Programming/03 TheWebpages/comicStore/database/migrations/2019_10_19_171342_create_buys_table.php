<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreateBuysTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('buys', function (Blueprint $table) {
            $table->increments('id');
            $table->integer('units_cart');
            $table->float('total', 10, 2); 
            $table->integer('valoration');
            $table->integer('user_id')->unsingned();
            $table->integer('article_id')->unsingned();
            $table->integer('cart_id')->unsingned();
            $table->integer('paymentmethod_id')->unsingned();
            $table->timestamps();
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('buys');
    }
}
