#pragma once
#include <stack>
#include <iomanip>
#include <deque>
#include "Log.h"
#include "Lan.h"
#include "GRB.h"
#include "LT.h"

#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3


#define MFST_TRACE_START(LOG)		*log.stream	<< std::setw(4) << std::left << "Шаг" << ':'\
												<< std::setw(35) << std::left << " Правило"\
												<< std::setw(50) << std::left << " Входная лента"\
												<< std::setw(20) << std::left << " Стек" << std::endl;
#define MFST_TRACE1(LOG)			*log.stream <<std::setw(4)<<std::left<<++FST_TRACE_n<<": " \
												<<std::setw(35)<<std::left<<rule.getCRule(rbuf,nrulechain)\
												<<std::setw(50)<<std::left<<getCLenta(lbuf, lenta_position)\
												<<std::setw(20)<<std::left<<getCSt(sbuf)\
												<<std::endl;
#define MFST_TRACE2(LOG)			*log.stream <<std::setw(4)<<std::left<<FST_TRACE_n<<": "\
												<<std::setw(35)<<std::left<<" "\
												<<std::setw(50)<<std::left<<getCLenta(lbuf, lenta_position)\
												<<std::setw(20)<<std::left<<getCSt(sbuf)\
												<<std::endl;
#define MFST_TRACE3(LOG)			*log.stream <<std::setw(4)<<std::left<<++FST_TRACE_n<<": "\
												<<std::setw(35)<<std::left<<" "\
												<<std::setw(50)<<std::left<<getCLenta(lbuf, lenta_position)\
												<<std::setw(20)<<std::left<<getCSt(sbuf)\
												<<std::endl;
#define MFST_TRACE4(LOG, c)			*log.stream <<std::setw(4)<<std::left<<++FST_TRACE_n<<": "<<std::setw(25)<<std::left<<c<<std::endl;

#define MFST_TRACE5(LOG, c)			*log.stream <<std::setw(4)<<std::left<<FST_TRACE_n<<": "<<std::setw(25)<<std::left<<c<<std::endl;

#define MFST_TRACE6(LOG, c, k)		*log.stream <<std::setw(4)<<std::left<<FST_TRACE_n<<": "<<std::setw(25)<<std::left<<c<<k<<std::endl;

#define MFST_TRACE7(LOG)			*log.stream <<std::setw(4)<<std::internal<<state.lenta_position<<"\t |  "\
												<<std::setw(25)<<std::left<<rule.getCRule(rbuf,state.nrulechain)\
												<<std::endl;


//class my_stack_SHORT : public std::stack<short> {
//public :
//	using std::stack<short>::c;
//};

template <typename T>
class MyStack : public std::stack<T> {
public:
	using std::stack<T>::c;
};

//typedef MyStack<short> MFSTSTSTACK;
namespace MFST
{
	struct MfstState
	{
		short lenta_position;
		short nrule;
		short nrulechain;
		MyStack<short> st;
		MfstState();
		MfstState(short pposition, MyStack<short> pst, short pnrulechain);
		MfstState(short pposition, MyStack<short> pst, short pnrule, short pnrulechain);
	};

	struct Mfst
	{
		enum RC_STEP
		{
			NS_OK,
			NS_NORULE,
			NS_NORULECHAIN,
			NS_ERROR,
			TS_OK,
			TS_NOK,
			LENTA_END,
			SURPRISE
		};

		struct MfstDiagnosis
		{
			short lenta_position;
			RC_STEP rc_step;
			short nrule;
			short nrule_chain;
			MfstDiagnosis();
			MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain);
		} diagnosis[MFST_DIAGN_NUMBER];

		GRBALPHABET* lenta;
		int FST_TRACE_n = 0;
		short lenta_position;
		short nrule;
		short nrulechain;
		short lenta_size;
		GRB::Greibach grebach;
		LT::LexTable lex;

		MyStack<short> st;
		MyStack<MfstState> storestate;
		Mfst();
		Mfst(LT::LexTable plex, GRB::Greibach pgrebach);
		char* getCSt(char* buf);
		char* getCLenta(char* buf, short pos, short n = 25);
		char* getDiagnosis(short n, char* buf);
		bool savestate(Log::LOG log);
		bool restate(Log::LOG log);
		bool push_chain(GRB::Rule::Chain chain);
		RC_STEP step(Log::LOG log);
		bool start(Log::LOG log);
		bool savediagnosis(RC_STEP pprc_step);
		void printrules(Log::LOG &log);

		struct Deducation
		{
			short size;
			short* nrules;
			short* nrulechains;
			Deducation() { size = 0; nrules = 0; nrulechains = 0; }
		} deducation;
		bool savededucation();
	};
}