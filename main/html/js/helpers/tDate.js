

var tDate = function(data) {
    this.data = data;
    if (! ('date' in this.data)) {
        this.data.date = {};
    }

    this.updateEt();

    this.J2000MJD = 51544.5;
    this.J2000MJDsec = 4453444800.0;
};

/**
 * Update Jd and Date when data.et changes (seconds in J2000 reference frame).
 */
tDate.prototype.updateEt = function() {
    this._et2jd();
    this._jd2date();
};

tDate.prototype.updateJd = function() {
    this._jd2et();
    this._jd2date();
}

tDate.prototype.updateDate = function() {
    this._date2jd();
    this._jd2et();
};

tDate.prototype._jd2et = function() {
    this.data.et = this.data.jd * 86400.0 - this.J2000MJDsec;
};

tDate.prototype._et2jd = function() {
    this.data.jd = (this.data.et + this.J2000MJDsec) / 86400.0;
};

tDate.prototype._date2jd = function() {
    var i_a = this.idiv(14 - this.data.date.month, 12);
    var i_y = this.data.date.year - i_a;
    var i_m = this.data.date.month + 12 * i_a - 3;

    var i_jdn = this.data.date.day + this.idiv(153 * i_m + 2, 5) + 365 * i_y + this.idiv(i_y, 4) - this.idiv(i_y, 100) + this.idiv(i_y, 400) - 678882;

    this.data.jd = i_jdn + this.data.date.hour/24. + this.data.date.min/1440. + this.data.date.sec / 86400.;
};

tDate.prototype._jd2date = function() {
    var i_jdn = Math.floor(this.data.jd) + 2400001;

    var i_j = i_jdn + 32044;
    var i_g = this.idiv(i_j, 146097);
    var i_dg =  i_j % 146097;

    var i_c = this.idiv((this.idiv(i_dg, 36524) + 1) * 3, 4);
    var i_dc = i_dg - i_c * 36524;

    var i_b = this.idiv(dc, 1461);
    var i_db = i_dc % 1461;

    var i_a = this.idiv((this.idiv(i_db, 365) + 1) * 3, 4);
    var i_da = i_db - a * 365;

    var i_y = i_g * 400 + i_c * 100 + i_b * 4 + i_a;
    var i_m = this.idiv(i_da * 5 + 308, 153) - 2;
    var i_d = i_da - this.idiv((m + 4) * 153, 5) + 122;


    this.data.date.year = i_y - 4800 + this.idiv(i_m + 2, 12);
    this.data.date.month = (i_m + 2) % 12 + 1;
    this.data.date.day = i_d + 1;

    var d_t = this.data.jd - Math.floor(this.data.jd);

    this.data.date.hour = Math.floor(t * 24);
    this.data.date.min = Math.floor(t*1440 - 60 * this.data.date.hour);
    this.data.date.sec = t*86400. - 3600. * this.data.date.hour - 60.*this.data.date.min;
};

tDate.prototype.idiv = function(a, b) {
    return ~~(a/b);
};
