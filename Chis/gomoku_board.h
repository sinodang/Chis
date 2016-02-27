#ifndef _CHIS_BOARD
#define _CHIS_BOARD
#include "chis_config.h"
namespace chis 
{

	///////////////����Ʋ�࣬4�ֵ�����///////////////
	/*
	�����������
	��++������ǰһ����
	��--��������һ����
	��!=�����ж��Ƿ����
	��=�� ����ֵ
	��*�� �������ã����ص�����ָ��ĵ��ֵ
	������
	in_board():�жϵ������Ƿ��������ڣ�����ǣ�����true
	itor_n(int (&_b)[30][30], int _i, int _j) :���캯������Ҫint[30][30]��ʽ������, ����һ��������ꡣ
	*/

	////////////////////////////////
	struct Point {
		//������
		int x, y;
		Point() {}
		Point(int a, int b) :x(a), y(b) {}
		bool operator==(const Point&b)const {
			return x == b.x && y == b.y;
		}
	};
	struct _point_with_value {
		//����������ֵ
		Point first;
		int value;
		_point_with_value(Point _p, int _v) :first(_p), value(_v) {}
		bool operator<(const _point_with_value &a)const {
			return value > a.value;
		}
	};
	struct _depth_with_value_ {
		//���������ڵ�ֵ
		char depth;
		int value;
	};
	struct Patterns {
		//λ�ò��ܱ䣡������ֱ��Ѱַ��
		char one_s = 0;//0 ��һ
		char one_l = 0;//1 ��һ
		char two_s = 0;//2 �߶�
		char two_l = 0;//3 ���
		char three_s = 0;//4 ����
		char three_l = 0;//5 ����
		char four_b = 0;//6 ����
		char four_l = 0;//7 ����
		char wined = 0;//8 ʤ�������֣�����ƴ����
		Patterns& operator+=(const Patterns &a) {
			wined += a.wined;
			four_l += a.four_l;
			four_b += a.four_b;
			three_l += a.three_l;
			three_s += a.three_s;
			two_l += a.two_l;
			two_s += a.two_s;
			one_l += a.one_l;
			one_s += a.one_s;
			return *this;
		}
		Patterns& operator-=(const Patterns &a) {
			wined -= a.wined;
			four_l -= a.four_l;
			four_b -= a.four_b;
			three_l -= a.three_l;
			three_s -= a.three_s;
			two_l -= a.two_l;
			two_s -= a.two_s;
			one_l -= a.one_l;
			one_s -= a.one_s;
			return *this;
		}
		Patterns operator-(const Patterns &a)const {
			Patterns temp = *this;
			return (temp -= a);
		}
		void reset() {
			one_s = 0;//0 ��һ
			one_l = 0;//1 ��һ
			two_s = 0;//2 �߶�
			two_l = 0;//3 ���
			three_s = 0;//4 ����
			three_l = 0;//5 ����
			four_b = 0;//6 ����
			four_l = 0;//7 ����
			wined = 0;//8 ʤ�������֣�����ƴ����
		}
	};
	struct patterns_pair {
		Patterns first;
		Patterns second;
		void operator+=(const patterns_pair &r) {
			first += r.first;
			second += r.second;
		}
		void operator-=(const patterns_pair &r) {
			first -= r.first;
			second -= r.second;
		}
		void reset() {
			first.reset();
			second.reset();
		}
	};
	struct Parameters {
		int one_s = 3;
		int one_l = 15;
		int two_s = 45;
		int two_l = 180;
		int three_s = 280;
		int three_l = 485;
		int four_b = 580;
		int four_l = 850;
		int wined = 10000000;
		/*
		int one_s = 3;
		int one_l = 15;
		int two_s = 45;
		int two_l = 180;
		int three_s = 280;
		int three_l = 485;
		int four_b = 580;
		int four_l = 850;
		int wined = 10000000;*/
		Parameters() {}
		Parameters(int os, int ol, int ts, int tl, int ths, int thl, int fb, int fl, int w)
			:one_s(os), one_l(ol), two_s(ts), two_l(tl), three_s(ths), three_l(thl), four_b(fb), four_l(fl), wined(w) {
		}
		int operator*(const Patterns &cnt) const {
			return
				wined * cnt.wined +
				four_l * cnt.four_l +
				four_b * cnt.four_b +
				three_l * cnt.three_l +
				three_s * cnt.three_s +
				two_l *cnt.two_l +
				two_s * cnt.two_s +
				one_l * cnt.one_l +
				one_s * cnt.one_s;
		}
	};
	struct chis_config {
		int VCF_DEPTH;
		int VCT_DEPTH;
		int VC2_DEPTH;
		int MAX_DEPTH;//�����������
		int MAX_P;//�����������һ���ѡ�ŷ��ĸ���
		int SEARCH_TIME;
		chis_config(int vf, int vt, int v2, int md, int mp, int st)
			:VCF_DEPTH(vf), VCT_DEPTH(vt), VC2_DEPTH(v2), MAX_DEPTH(md), MAX_P(mp), SEARCH_TIME(st) {
		}
		void override_config() {
			chis::VCF_DEPTH = VCF_DEPTH;
			chis::VCT_DEPTH = VCT_DEPTH;
			chis::VC2_DEPTH = VC2_DEPTH;
			chis::MAX_DEPTH = MAX_DEPTH;//�����������
			chis::MAX_P = MAX_P;//�����������һ���ѡ�ŷ��ĸ���
			chis::VC_DEPTH = VCT_DEPTH + VCF_DEPTH + VC2_DEPTH;
			chis::SEARCH_TIME = SEARCH_TIME;
		}
	};
	////////////////////////////////
	class Board {
		class itor_1 {//����
		public:
			itor_1(int(&_b)[30][30], int _i, int _j) : b(_b), i(_i), j(_j) {}
			bool in_board() {
				return j >= 0 && j < SIZE;
			}
			itor_1& operator++() {
				++j;
				return *this;
			}
			itor_1& operator--() {
				--j;
				return *this;
			}
			int operator*() {
				return b[i][j];
			}
			bool operator!=(itor_1 &a) {
				return j != a.j;//�仯��ֻ��j
			}
			void operator=(itor_1 &a) {
				i = a.i;
				j = a.j;
			}
		private:
			int i, j;
			int(&b)[30][30];
		};
		class itor_2 {//����
		public:
			itor_2(int(&_b)[30][30], int _i, int _j) : b(_b), i(_i), j(_j) {}
			bool in_board() {
				return i >= 0 && i < SIZE;
			}
			itor_2& operator++() {
				++i;
				return *this;
			}
			itor_2& operator--() {
				--i;
				return *this;
			}
			int operator*() {
				return b[i][j];
			}
			bool operator!=(itor_2 &a) {
				return i != a.i;
			}
			void operator=(itor_2 &a) {
				i = a.i;
				j = a.j;
			}
		private:
			int i, j;
			int(&b)[30][30];
		};
		class itor_3 {//Ʋ��
		public:
			itor_3(int(&_b)[30][30], int _i, int _j) : b(_b), i(_i), j(_j) {}
			bool in_board() {
				return i >= 0 && i < SIZE && j >= 0 && j < SIZE;
			}
			itor_3& operator++() {
				++i, ++j;
				return *this;
			}
			itor_3& operator--() {
				--i, --j;
				return *this;
			}
			int operator*() {
				return b[i][j];
			}
			bool operator!=(itor_3 &a) {
				return i != a.i || j != a.j;
			}
			void operator=(itor_3 &a) {
				i = a.i;
				j = a.j;
			}
		private:
			int i, j;
			int(&b)[30][30];
		};
		class itor_4 {//����
		public:
			itor_4(int(&_b)[30][30], int _i, int _j) : b(_b), i(_i), j(_j) {}
			bool in_board() {
				return i >= 0 && i < SIZE && j >= 0 && j < SIZE;
			}
			itor_4& operator++() {
				++i, --j;
				return *this;
			}
			itor_4& operator--() {
				--i, ++j;
				return *this;
			}
			int operator*() {
				return b[i][j];
			}
			bool operator!=(itor_4 &a) {
				return i != a.i || j != a.j;
			}
			void operator=(itor_4 &a) {
				i = a.i;
				j = a.j;
			}
		private:
			int i, j;
			int(&b)[30][30];
		};
	public:
		//�����ȡֵ
		const int* operator[](int i) const {
			return b[i];
		}
		//���Ӻ�����ԭ���ϲ����������Ӹ�����һ�����ӣ���Ϊ�����ܲ������õļ��
		//ά��hask_key
		//ά��step(move_count)
		//ά��_patterns
		//...
		int set(int i, int j, int c);
		int value() {
			return default_para*(_patterns.first - _patterns.second);
		}
		int nega_value();
		int evaluate();
		//��������c��i��j���õ��ģ��Ե㣩��ֵ����Ӱ�����̱�����
		int try_set(int i, int j, int c);
		int try_set_nega(int i, int j, int c);
		int point_eval(int i, int j, int try_c);
		//�õ���ǰ���̵�����ͳ�Ʊ�
		patterns_pair& get_patterns() {
			return _patterns;
		}
		//�õ�i��j ������ߣ�����Ʋ�ࣩ����ͳ�Ʊ���
		patterns_pair get_patterns(int i, int j);
		//��������c��i��j���õ�������ͳ�Ʊ�����Ӱ�����̱�����
		patterns_pair get_patterns(int i, int j, int c);
		Patterns get_update(int i, int j, int try_c, int ret_color = 0);
		//�����ͱ��жϣ��Ƿ����ж��֡�
		int have_winner();
		//����ͳ��
		int move_count() {
			return step;
		}
		//�����õ���������
		const Patterns& black_patterns() {
			return _patterns.first;
		}
		//�����õ���������
		const Patterns& white_patterns() {
			return _patterns.second;
		}
		__int64 hash_value() const {
			//�������̵�64λhashֵ
			return hash_key;
		}
		//reset����,��ԭ����
		void clear() {
			for(int i = 0; i < SIZE; ++i) {
				for(int j = 0; j < SIZE; ++j) {
					b[i][j] = 0;
				}
			}
			hash_key = 0;
			step = 0;
			_patterns.reset();
			CHIS_CONFIG.override_config();
		}
		bool operator==(const Board &b2) const {
			//�ж������Ƿ����
			for(int i = 0; i < SIZE; ++i) {
				for(int j = 0; j < SIZE; ++j) {
					if(b[i][j] != b2[i][j]) {
						return false;
					}
				}
			}
			return true;
		}
		bool operator<(const Board &b2) const {
			//�ж�����˳��
			return hash_key < b2.hash_key;
		}
	private:
		int b[30][30] = {};//board ����
		__int64 hash_key = 0;//���̵�64λhashֵ
		patterns_pair _patterns;//��̬������ͳ�Ʊ�
		int step = 0;//��move_count

		//TODO����ʷ���ӱ�
		Point last_set;//���һ�����ӵ�λ��
		int last_set_color;//���һ�����ӵ���ɫ

		//����ͳ�Ʊ�������set֮����á�
		inline void Board::update_patterns();
		template<typename itor>
		// ͨ���������������Ͳ��ӵ�count��
		inline void  patterns_of_line_add(patterns_pair &count, itor &begin);
		template<typename itor>
		//ͨ���������������Ͳ���count�ϼ�ȥ
		inline void  patterns_of_line_dec(patterns_pair &count, itor &begin);
		//���ڵ������ʼ������ (������lan��de��xie��daima�����ṩβ�������)
		//���ڱ�����p���ڵ�����ֱ�ߣ�����Ʋ�ࣩ
		itor_1 begin1(Point p) {
			return itor_1(b, p.x, 0);
		}
		itor_2 begin2(Point p) {
			return itor_2(b, 0, p.y);
		}
		itor_3 begin3(Point p) {
			return p.x <= p.y ?
				itor_3(b, 0, p.y - p.x) :
				itor_3(b, p.x - p.y, 0);
		}
		itor_4 begin4(Point p) {
			return p.x + p.y >= SIZE ?
				itor_4(b, p.x + p.y - (SIZE - 1), SIZE - 1) :
				itor_4(b, 0, p.x + p.y);
		}
		//begin_white ��˵�����İ�ɫ�� ����ࣩ begin_black ��˵�����ĺ�ɫ�� (���߱�Ե)
		template<typename itor>
		inline itor begin_white(Point p) {
			itor bg(b, p.x, p.y);
			int n = 6, sp = 0;
			--bg;
			while(sp < 4 && --n && *bg != -1 && bg.in_board()) {
				if(*bg == 0) {
					++sp;
				}
				else {
					sp = 0;
				}
				--bg;
			}
			//*bg == -1 || bg����������
			return bg;
		}
		template<typename itor>
		inline itor begin_black(Point p) {
			itor bg(b, p.x, p.y);
			int n = 6, sp = 0;
			--bg;
			while(sp < 4 && --n && *bg != 1 && bg.in_board()) {
				if(*bg == 0) {
					++sp;
				}
				else {
					sp = 0;
				}
				--bg;
			}
			//*bg == 1 || bg���������� || n == 0
			return bg;
		}
		//end_white ��˵�����İ�ɫ�㣨�Ҳࣩ end_black ��˵�����ĺ�ɫ�� (���߱�Ե)
		template<typename itor>
		inline itor end_white(Point p) {
			itor bg(b, p.x, p.y);
			int n = 6, sp = 0;
			++bg;
			while(sp < 4 && --n && *bg != -1 && bg.in_board()) {
				if(*bg == 0) {
					++sp;
				}
				else {
					sp = 0;
				}
				++bg;
			}
			//*bg == -1 || bg���������� || n == 0
			return bg;
		}
		template<typename itor>
		inline itor end_black(Point p) {
			itor bg(b, p.x, p.y);
			int n = 6, sp = 0;
			++bg;
			while(sp < 4 && --n && *bg != 1 && bg.in_board()) {
				if(*bg == 0) {
					++sp;
				}
				else {
					sp = 0;
				}
				++bg;
			}
			//*bg == 1 || bg����������
			return bg;
		}
	};
	////////////��ֵ��Ϣ////////////
	
}
#endif